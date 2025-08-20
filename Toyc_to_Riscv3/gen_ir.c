#include "gen_ir.h"
#include "ir.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 静态变量用于生成唯一的临时变量和标签 */
static int temp_id = 0;
static int label_id = 0;

static char* new_temp() {
    static char buf[32];
    sprintf(buf, "t%d", temp_id++);
    return strdup(buf);
}

static char* new_label(const char* prefix) {
    static char buf[32];
    sprintf(buf, "%s%d", prefix, label_id++);
    return strdup(buf);
}

/* --- 符号表与作用域管理 --- */
typedef struct Sym { char name[64]; char reg[32]; struct Sym* next; } Sym;
typedef struct Scope { Sym* head; struct Scope* next; } Scope;
static Scope* scope_stack = NULL;

static void scope_push() {
    Scope* s = (Scope*)malloc(sizeof(Scope));
    s->head = NULL; s->next = scope_stack;
    scope_stack = s;
}

static void scope_pop() {
    if (!scope_stack) return;
    Scope* s = scope_stack;
    Sym* p = s->head;
    while(p) { Sym* q = p->next; free(p); p = q; }
    scope_stack = s->next;
    free(s);
}

static void sym_set(const char* name, const char* reg) {
    for (Sym* p = scope_stack->head; p; p = p->next) {
        if (strcmp(p->name, name) == 0) {
            strncpy(p->reg, reg, sizeof(p->reg) - 1);
            return;
        }
    }
    Sym* n = (Sym*)malloc(sizeof(Sym));
    strncpy(n->name, name, sizeof(n->name) - 1);
    strncpy(n->reg, reg, sizeof(n->reg) - 1);
    n->next = scope_stack->head;
    scope_stack->head = n;
}

static const char* sym_get(const char* name) {
    for (Scope* s = scope_stack; s; s = s->next) {
        for (Sym* p = s->head; p; p = p->next) {
            if (strcmp(p->name, name) == 0) return p->reg;
        }
    }
    return NULL;
}

/* --- 循环控制栈 (break/continue) --- */
typedef struct LoopCtx { char brk[32]; char cont[32]; struct LoopCtx* next; } LoopCtx;
static LoopCtx* loop_stack = NULL;

static void loop_push(const char* brk, const char* cont) {
    LoopCtx* n = (LoopCtx*)malloc(sizeof(LoopCtx));
    strncpy(n->brk, brk, sizeof(n->brk) - 1);
    strncpy(n->cont, cont, sizeof(n->cont) - 1);
    n->next = loop_stack;
    loop_stack = n;
}

static void loop_pop() {
    if (!loop_stack) return;
    LoopCtx* t = loop_stack;
    loop_stack = t->next;
    free(t);
}

/* --- 前向声明 --- */
static char* gen_expr(ASTNode* e);
static void gen_stmt(ASTNode* s);


/* 为逻辑与/或生成带短路求值的 IR */
static char* gen_logical_short(Operator op, ASTNode* a, ASTNode* b) {
    char* dst = new_temp();
    char* L_end = new_label("Lend_");

    if (op == OP_LAND) {
        char* L_false = new_label("Lfalse_");
        char* ra = gen_expr(a);
        ir_emit_ifz(ra, L_false);
        char* rb = gen_expr(b);
        ir_emit_bin(OP_NE, dst, rb, "0"); // result = (rb != 0)
        ir_emit_goto(L_end);
        ir_emit_label(L_false);
        ir_emit_loadi(dst, 0);
        ir_emit_label(L_end);
    } else { // OP_LOR
        char* L_eval_b = new_label("Lor_eval_b_");
        char* ra = gen_expr(a);
        ir_emit_ifz(ra, L_eval_b); // if a is 0, evaluate b
        ir_emit_loadi(dst, 1);     // else, result is 1
        ir_emit_goto(L_end);
        ir_emit_label(L_eval_b);
        char* rb = gen_expr(b);
        ir_emit_bin(OP_NE, dst, rb, "0"); // result = (rb != 0)
        ir_emit_label(L_end);
    }
    return dst;
}

/* 递归生成表达式的 IR */
static char* gen_expr(ASTNode* e) {
    if (!e) return strdup("0");

    switch (e->type) {
        case NODE_NUMBER: {
            char* r = new_temp();
            ir_emit_loadi(r, e->data.number);
            return r;
        }
        case NODE_ID: {
            const char* r = sym_get(e->data.id);
            if (!r) {
                fprintf(stderr, "Semantic Error: Identifier '%s' used before declaration.\n", e->data.id);
                char* z = new_temp(); ir_emit_loadi(z, 0); return z;
            }
            return strdup(r);
        }
        case NODE_PRIMARY: { // 函数调用
            ASTNode* p = e->data.primary.args;
            ASTNode* arg_nodes[256]; int n = 0;
            while(p && n < 256) { arg_nodes[n++] = p; p = p->next; }
            for (int i = n - 1; i >= 0; --i) {
                char* ri = gen_expr(arg_nodes[i]);
                ir_emit_arg(ri);
            }
            char* rd = new_temp();
            ir_emit_call(rd, e->data.primary.id, n);
            return rd;
        }
        case NODE_EXPR: {
            Operator op = (Operator)e->data.expr.op;
            if (e->data.expr.left == NULL) { // 一元操作符
                char* r = gen_expr(e->data.expr.right);
                if (op == OP_PLUS) return r;
                if (op == OP_MINUS) {
                    char* z = new_temp(); ir_emit_loadi(z, 0);
                    char* d = new_temp();
                    // --- 唯一的修改在此处：将 OP_SUB 改为 ast.h 中定义的 OP_MINUS ---
                    ir_emit_bin(OP_MINUS, d, z, r);
                    return d;
                }
                if (op == OP_NOT) { // !r 等价于 (r == 0)
                    char* d = new_temp();
                    ir_emit_bin(OP_EQ, d, r, "0");
                    return d;
                }
            }

            if (op == OP_LOR || op == OP_LAND) {
                return gen_logical_short(op, e->data.expr.left, e->data.expr.right);
            }

            if (op == OP_INDEX) {
                 fprintf(stderr, "Warning: Array access IR generation is not fully implemented.\n");
                 char* z = new_temp(); ir_emit_loadi(z, 0); return z;
            }

            char* a = gen_expr(e->data.expr.left);
            char* b = gen_expr(e->data.expr.right);
            char* d = new_temp();
            ir_emit_bin(op, d, a, b);
            return d;
        }
        default: break;
    }
    char* z = new_temp(); ir_emit_loadi(z, 0); return z;
}

/* 生成语句的 IR */
static void gen_stmt(ASTNode* s) {
    if (!s) return;

    switch(s->type) {
        case NODE_BLOCK: {
            scope_push();
            ASTNode* p = s->data.block.stmt_list;
            ASTNode* stmts[1024]; int n=0;
            while (p && n<1024) { stmts[n++]=p; p=p->next; }
            for (int i=n-1; i>=0; --i) gen_stmt(stmts[i]);
            scope_pop();
            break;
        }
        case NODE_STMT: {
            switch (s->data.stmt.stmt_type) {
                case STMT_EMPTY: break;
                case STMT_EXPR: gen_expr(s->data.stmt.expr); break;
                case STMT_ASSIGN: {
                    ASTNode* as = s->data.stmt.expr;
                    if (as->data.expr.left->type == NODE_ID) {
                        char* rv = gen_expr(as->data.expr.right);
                        const char* bound = sym_get(as->data.expr.left->data.id);
                        if (!bound) {
                            fprintf(stderr, "Semantic Error: Assignment to undeclared identifier '%s'\n", as->data.expr.left->data.id);
                        } else {
                            ir_emit_move((char*)bound, rv);
                        }
                    } else {
                        fprintf(stderr, "Warning: Array element assignment is not implemented.\n");
                    }
                    break;
                }
                case STMT_DECL: {
                    ASTNode* decl_expr = s->data.stmt.expr;
                    if (decl_expr->data.expr.op == OP_ASSIGN) {
                        ASTNode* idn = decl_expr->data.expr.left;
                        char* r = new_temp();
                        sym_set(idn->data.id, r);
                        char* rv = gen_expr(decl_expr->data.expr.right);
                        ir_emit_move(r, rv);
                    } else if (decl_expr->data.expr.op == OP_INDEX) {
                        ASTNode* idn = decl_expr->data.expr.left;
                        sym_set(idn->data.id, new_temp());
                        fprintf(stderr, "Warning: Array declaration IR is not fully implemented (memory allocation).\n");
                    }
                    break;
                }
                case STMT_IF: {
                    char* Lelse = new_label("Lelse_");
                    char* Lend  = new_label("Lend_");
                    char* cond = gen_expr(s->data.stmt.expr);
                    ir_emit_ifz(cond, Lelse);
                    gen_stmt(s->data.stmt.then_stmt);
                    ir_emit_goto(Lend);
                    ir_emit_label(Lelse);
                    if (s->data.stmt.else_stmt) gen_stmt(s->data.stmt.else_stmt);
                    ir_emit_label(Lend);
                    break;
                }
                case STMT_WHILE: {
                    char* Lcond = new_label("Lwhile_cond_");
                    char* Lbody = new_label("Lwhile_body_");
                    char* Lend  = new_label("Lwhile_end_");
                    loop_push(Lend, Lcond);
                    ir_emit_label(Lcond);
                    char* c = gen_expr(s->data.stmt.expr);
                    ir_emit_ifz(c, Lend);
                    ir_emit_label(Lbody);
                    gen_stmt(s->data.stmt.then_stmt);
                    ir_emit_goto(Lcond);
                    ir_emit_label(Lend);
                    loop_pop();
                    break;
                }
                case STMT_BREAK: if (loop_stack) ir_emit_goto(loop_stack->brk); break;
                case STMT_CONTINUE: if (loop_stack) ir_emit_goto(loop_stack->cont); break;
                case STMT_RETURN: {
                    if (s->data.stmt.expr) {
                        char* r = gen_expr(s->data.stmt.expr);
                        ir_emit_ret(r);
                    } else {
                        ir_emit_ret(NULL);
                    }
                    break;
                }
            }
            break;
        }
        default: break;
    }
}

/* 生成函数的 IR */
static void gen_func(ASTNode* f) {
    ir_emit_func_begin(f->data.func_def.func_name);
    scope_push();
    
    ASTNode* p = f->data.func_def.params;
    ASTNode* params[256]; int n = 0;
    while(p && n < 256) { params[n++] = p; p = p->next; }
     for (int i = n - 1; i >= 0; --i) {
        char* r = new_temp();
        sym_set(params[i]->data.param.name, r);
        char param_reg[16];
        sprintf(param_reg, "param%d", n - 1 - i);
        ir_emit_move(r, param_reg);
    }

    gen_stmt(f->data.func_def.block);
    
    ir_emit_ret(NULL); 
    
    scope_pop();
    ir_emit_func_end(f->data.func_def.func_name);
}

/* IR 生成的主入口函数 */
void gen_comp_unit_ir(ASTNode* root) {
    ir_clear();
    temp_id = label_id = 0;
    
    ASTNode* f = root->data.comp_unit.func_def;
    ASTNode* funcs[512]; int n = 0;
    while (f && n < 512) { funcs[n++] = f; f = f->next; }
    for (int i = n - 1; i >= 0; --i) {
        gen_func(funcs[i]);
    }
}

/* 清理 IR 占用的资源 */
void free_ir(void) {
    ir_clear();
}
