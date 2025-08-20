#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gen_riscv.h"
#include "ir.h"
#include "ast.h"

// --- 数据结构 ---
typedef struct VarMap {
    char name[32];
    int offset;
    struct VarMap* next;
} VarMap;

// 记录正在生成的函数的栈大小（供 callee 在 emit_load 中读取 paramN >=8 的偏移）
static int current_stack_size = 0;

// --- 辅助函数 ---
static int is_number(const char* s) {
    if (!s || *s == '\0') return 0;
    char *endptr;
    strtol(s, &endptr, 10);
    return (*endptr == '\0');
}

static VarMap* find_var(VarMap* head, const char* name) {
    for (VarMap* p = head; p; p = p->next) {
        if (strcmp(p->name, name) == 0) return p;
    }
    return NULL;
}

static void add_var_to_map(VarMap** head, const char* name, int* current_offset) {
    if (!name || name[0] == '\0' || is_number(name) || strncmp(name, "param", 5) == 0 || find_var(*head, name)) {
        return;
    }
    VarMap* new_var = (VarMap*)malloc(sizeof(VarMap));
    strncpy(new_var->name, name, 31);
    new_var->name[31] = '\0';
    new_var->offset = *current_offset;
    *current_offset += 4;
    new_var->next = *head;
    *head = new_var;
}

static void free_map(VarMap* head) {
    while (head) {
        VarMap* t = head->next;
        free(head);
        head = t;
    }
}

// --- 代码生成辅助函数 ---
// 注意：所有对局部变量/param 的内存访问都用 s0 作为基址（frame pointer），
// 以便在函数体内多次调整 sp 时地址稳定。
static void emit_load(FILE* out, const char* operand, const char* reg, VarMap* map) {
    if (!operand) {
        fprintf(out, "  li %s, 0\n", reg);
        return;
    }
    if (is_number(operand)) {
        fprintf(out, "  li %s, %s\n", reg, operand);
    } else if (strncmp(operand, "param", 5) == 0) {
        int param_idx = atoi(operand + 5);
        if (param_idx < 8) {
            fprintf(out, "  mv %s, a%d\n", reg, param_idx);
        } else {
            // param >= 8: callee 从它自己的 frame pointer(s0) + current_stack_size + offset 处读
            fprintf(out, "  lw %s, %d(s0)\n", reg, current_stack_size + (param_idx - 8) * 4);
        }
    } else {
        VarMap* var = find_var(map, operand);
        if (var) {
            fprintf(out, "  lw %s, %d(s0)\n", reg, var->offset);
        } else {
            fprintf(out, "  # COMPILE_ERROR: variable '%s' not defined!\n", operand);
            fprintf(out, "  li %s, 0\n", reg);
        }
    }
}

static void emit_store(FILE* out, const char* var_name, const char* reg, VarMap* map) {
    VarMap* var = find_var(map, var_name);
    if (var) {
        fprintf(out, "  sw %s, %d(s0)\n", reg, var->offset);
    } else {
        fprintf(out, "  # COMPILE_ERROR: store to undefined variable '%s'!\n", var_name);
    }
}

// --- 主生成函数 ---
void gen_riscv(FILE* out) {
    if (!out) {
        perror("Invalid output stream");
        return;
    }

    fprintf(out, ".text\n");
    IR* const ir_list_head = ir_head;

    IR* current_ir = ir_list_head;
    while (current_ir) {
        if (current_ir->op == IR_FUNC_BEGIN) {
            const char* func_name = current_ir->a;
            VarMap* var_map = NULL;
            int current_offset = 0;

            // --- 第一遍：分析IR，构建变量->栈偏移的映射表 ---
            IR* p_scan = current_ir;
            while (p_scan && p_scan->op != IR_FUNC_END) {
                switch (p_scan->op) {
                    case IR_MOVE: case IR_LOADI: case IR_CALL: case IR_BIN:
                        add_var_to_map(&var_map, p_scan->a, &current_offset);
                        break;
                    default: break;
                }
                p_scan = p_scan->next;
            }

            // 为 ra 和 s0 各自保留 4 字节；所有变量偏移均以 s0 为基准
            int stack_size = current_offset + 8; // +4 for ra, +4 for s0
            if (stack_size % 16 != 0) {
                stack_size += 16 - (stack_size % 16);
            }
            current_stack_size = stack_size;  // 设置全局，供 emit_load 使用（callee 使用）

            // --- 函数序言 ---
            fprintf(out, "\n.globl %s\n", func_name);
            fprintf(out, "%s:\n", func_name);
            fprintf(out, "  addi sp, sp, -%d\n", stack_size);
            fprintf(out, "  sw ra, %d(sp)\n", stack_size - 4);
            fprintf(out, "  sw s0, %d(sp)\n", stack_size - 8);
            fprintf(out, "  mv s0, sp\n");

            // --- 第二遍：遍历IR，生成代码 ---
            IR* p_gen = current_ir->next;
            while (p_gen && p_gen->op != IR_FUNC_END) {
                switch (p_gen->op) {
                    case IR_LABEL:
                        fprintf(out, "%s:\n", p_gen->a);
                        break;
                    case IR_GOTO:
                        fprintf(out, "  j %s\n", p_gen->a);
                        break;
                    case IR_IFZ:
                        emit_load(out, p_gen->a, "t0", var_map);
                        fprintf(out, "  beqz t0, %s\n", p_gen->b);
                        break;
                    case IR_LOADI:
                        fprintf(out, "  li t0, %d\n", p_gen->extra);
                        emit_store(out, p_gen->a, "t0", var_map);
                        break;
                    case IR_MOVE:
                        emit_load(out, p_gen->b, "t0", var_map);
                        emit_store(out, p_gen->a, "t0", var_map);
                        break;
                    case IR_BIN:
                        emit_load(out, p_gen->b, "t0", var_map);
                        emit_load(out, p_gen->c, "t1", var_map);
                        #define BIN_OP(op) fprintf(out, "  " #op " t0, t0, t1\n")
                        switch ((Operator)p_gen->extra) {
                            case OP_PLUS: BIN_OP(add); break;
                            case OP_MINUS: BIN_OP(sub); break;
                            case OP_MUL: BIN_OP(mul); break;
                            case OP_DIV: BIN_OP(div); break;
                            case OP_MOD: BIN_OP(rem); break;
                            case OP_LT: BIN_OP(slt); break;
                            case OP_GT: BIN_OP(sgt); break;
                            case OP_LE: fprintf(out, "  sgt t0, t0, t1\n  xori t0, t0, 1\n"); break;
                            case OP_GE: fprintf(out, "  slt t0, t0, t1\n  xori t0, t0, 1\n"); break;
                            case OP_EQ: fprintf(out, "  sub t0, t0, t1\n  seqz t0, t0\n"); break;
                            case OP_NE: fprintf(out, "  sub t0, t0, t1\n  snez t0, t0\n"); break;
                            default: break;
                        }
                        #undef BIN_OP
                        emit_store(out, p_gen->a, "t0", var_map);
                        break;
                    case IR_RET:
                        if (p_gen->a && p_gen->a[0] != '\0') {
                            emit_load(out, p_gen->a, "a0", var_map);
                        } else {
                            fprintf(out, "  li a0, 0\n");
                        }
                        fprintf(out, "  j %s_epilogue\n", func_name);
                        break;
                    case IR_ARG:
                        // ARG 在生成 CALL 时收集处理，这里不直接生成
                        break;
                    case IR_CALL: {
                        int arg_count = p_gen->extra;

                        // 收集在当前 CALL 之前出现的 ARG 节点（按链表出现顺序）
                        IR* all_func_args[1024];
                        int total_args_found = 0;
                        IR* finder = current_ir->next;
                        while (finder != NULL && finder != p_gen) {
                            if (finder->op == IR_ARG) {
                                if (total_args_found < 1024) {
                                    all_func_args[total_args_found++] = finder;
                                }
                            }
                            finder = finder->next;
                        }

                        int first_arg_idx = total_args_found - arg_count;
                        if (first_arg_idx < 0) {
                            fprintf(out, "  # COMPILE_ERROR: Mismatched ARG instructions for call to %s\n", p_gen->b);
                        } else {
                            IR* args_in_order[1024];
                            for (int i = 0; i < arg_count; ++i) {
                                args_in_order[i] = all_func_args[first_arg_idx + i];
                            }

                            int extra_size = 0;
                            if (arg_count > 8) {
                                int extra_args = arg_count - 8;
                                int arg_words = extra_args * 4;
                                int pad = (arg_words % 16) ? (16 - (arg_words % 16)) : 0;
                                extra_size = arg_words + pad;
                                // allocate stack space for extra args (caller)
                                fprintf(out, "  addi sp, sp, -%d\n", extra_size);
                                // write extra args into the new stack area.
                                // but use s0 as stable base: sp = s0 - extra_size, so
                                // address of the j-th extra arg is ( -extra_size + j*4 )(s0)
                                for (int j = 0; j < extra_args; ++j) {
                                    IR* arg_node = args_in_order[8 + j];
                                    // load operand (locals/params read via s0)
                                    emit_load(out, arg_node->a, "t0", var_map);
                                    fprintf(out, "  sw t0, %d(s0)\n", -extra_size + j * 4);
                                }
                            }

                            // put first 8 args into a0..a7
                            for (int i = 0; i < arg_count && i < 8; ++i) {
                                IR* arg_node = args_in_order[i];
                                emit_load(out, arg_node->a, "t0", var_map);
                                fprintf(out, "  mv a%d, t0\n", i);
                            }

                            fprintf(out, "  call %s\n", p_gen->b);

                            if (p_gen->a && p_gen->a[0] != '\0') {
                                emit_store(out, p_gen->a, "a0", var_map);
                            }

                            if (extra_size > 0) {
                                fprintf(out, "  addi sp, sp, %d\n", extra_size);
                            }
                        }
                        break;
                    }
                    default:
                        break;
                } // switch
                p_gen = p_gen->next;
            } // while p_gen

            // --- 函数尾声 ---
            fprintf(out, "%s_epilogue:\n", func_name);
            fprintf(out, "  lw s0, %d(sp)\n", stack_size - 8);
            fprintf(out, "  lw ra, %d(sp)\n", stack_size - 4);
            fprintf(out, "  addi sp, sp, %d\n", stack_size);
            fprintf(out, "  ret\n");

            free_map(var_map);
            current_ir = p_gen;
        } // if func_begin

        if (current_ir) current_ir = current_ir->next;
    } // while current_ir
}