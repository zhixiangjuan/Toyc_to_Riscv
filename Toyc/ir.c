#include "ir.h"
#include <stdlib.h>
#include <string.h>

/* 全局变量，指向 IR 链表的头和尾 */
IR *ir_head = NULL, *ir_tail = NULL;

/* 创建一个新的 IR 节点并添加到链表末尾 */
static IR* node(IROp op) {
    IR *n = (IR*)malloc(sizeof(IR));
    memset(n, 0, sizeof(*n));
    n->op = op;
    n->next = NULL;
    if (!ir_head) {
        ir_head = ir_tail = n;
    } else {
        ir_tail->next = n;
        ir_tail = n;
    }
    return n;
}

/* 清空整个 IR 链表 */
void ir_clear(void) {
    IR *p = ir_head;
    while (p) {
        IR *q = p->next;
        free(p);
        p = q;
    }
    ir_head = ir_tail = NULL;
}

/* IR 指令发射函数实现 */
void ir_emit_func_begin(const char *name) {
    IR *n = node(IR_FUNC_BEGIN);
    strncpy(n->a, name, sizeof(n->a)-1);
}

void ir_emit_func_end(const char *name) {
    IR *n = node(IR_FUNC_END);
    strncpy(n->a, name, sizeof(n->a)-1);
}

void ir_emit_label(const char *label) {
    IR *n = node(IR_LABEL);
    strncpy(n->a, label, sizeof(n->a)-1);
}

void ir_emit_goto(const char *label) {
    IR *n = node(IR_GOTO);
    strncpy(n->a, label, sizeof(n->a)-1);
}

void ir_emit_ifz(const char *reg, const char *label) {
    IR *n = node(IR_IFZ);
    strncpy(n->a, reg, sizeof(n->a)-1);
    strncpy(n->b, label, sizeof(n->b)-1);
}

void ir_emit_move(const char *dst, const char *src) {
    IR *n = node(IR_MOVE);
    strncpy(n->a, dst, sizeof(n->a)-1);
    strncpy(n->b, src, sizeof(n->b)-1);
}

void ir_emit_loadi(const char *dst, int imm) {
    IR *n = node(IR_LOADI);
    strncpy(n->a, dst, sizeof(n->a)-1);
    n->extra = imm;
}

/* --- 修改：ir_emit_bin 的参数类型现在是 Operator --- */
void ir_emit_bin(Operator op, const char *dst, const char *lhs, const char *rhs) {
    IR *n = node(IR_BIN);
    n->extra = (int)op; // 将操作符存入 extra 字段
    strncpy(n->a, dst, sizeof(n->a)-1);
    strncpy(n->b, lhs, sizeof(n->b)-1);
    strncpy(n->c, rhs, sizeof(n->c)-1);
}

void ir_emit_ret(const char *reg) {
    IR *n = node(IR_RET);
    if (reg) {
        strncpy(n->a, reg, sizeof(n->a)-1);
    }
}

void ir_emit_arg(const char *reg) {
    IR *n = node(IR_ARG);
    strncpy(n->a, reg, sizeof(n->a)-1);
}

void ir_emit_call(const char *dst, const char *fname, int nargs) {
    IR *n = node(IR_CALL);
    strncpy(n->a, dst, sizeof(n->a)-1);
    strncpy(n->b, fname, sizeof(n->b)-1);
    n->extra = nargs;
}

/* --- 修改：op2str 的参数类型现在是 Operator --- */
static const char* op2str(Operator op) {
    switch(op){
        case OP_PLUS: return "+";
        case OP_MINUS: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_MOD: return "%";
        case OP_LT:  return "<";
        case OP_GT:  return ">";
        case OP_LE:  return "<=";
        case OP_GE:  return ">=";
        case OP_EQ:  return "==";
        case OP_NE:  return "!=";
        /* OP_LOR, OP_LAND, OP_NOT, OP_ASSIGN, OP_INDEX 不会经过此函数 */
        default: return "?";
    }
}

/*
 * 打印所有 IR 指令。
 * 函数名已从 ir_print 修改为 print_ir。
 */
void print_ir(void) {
    for (IR *p = ir_head; p; p = p->next) {
        switch (p->op) {
            case IR_FUNC_BEGIN: printf("func %s:\n", p->a); break;
            case IR_FUNC_END:   printf("end %s\n\n", p->a); break;
            case IR_LABEL:      printf("%s:\n", p->a); break;
            case IR_GOTO:       printf("  goto %s\n", p->a); break;
            case IR_IFZ:        printf("  ifz %s goto %s\n", p->a, p->b); break;
            case IR_MOVE:       printf("  %s = %s\n", p->a, p->b); break;
            case IR_LOADI:      printf("  %s = %d\n", p->a, p->extra); break;
            case IR_BIN:        printf("  %s = %s %s %s\n", p->a, p->b, op2str((Operator)p->extra), p->c); break;
            case IR_RET:
                if (p->a[0]) printf("  return %s\n", p->a);
                else printf("  return\n");
                break;
            case IR_ARG:        printf("  arg %s\n", p->a); break;
            case IR_CALL:       printf("  %s = call %s, %d\n", p->a, p->b, p->extra); break;
        }
    }
}
