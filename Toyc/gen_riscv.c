#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 【致命Bug修正】使用正确的C语言头文件
#include <ctype.h>
#include "gen_riscv.h"
#include "ir.h"
#include "ast.h"

// --- 数据结构 (无修改) ---
typedef struct Var {
    char ir_temp_name[32];
    int offset;
    struct Var *next;
} Var;

#define NUM_TEMP_REGS 7
static const char* temp_reg_names[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6"};
typedef struct {
    char ir_temp_name[32];
    int in_use;
} TempRegMap;

static TempRegMap temp_reg_map[NUM_TEMP_REGS];
static Var *spilled_vars_head = NULL;
static int next_spill_offset = 0;

// --- 辅助函数 (无修改) ---
static void reset_spilled_vars() {
    while (spilled_vars_head) {
        Var *t = spilled_vars_head->next;
        free(spilled_vars_head);
        spilled_vars_head = t;
    }
    next_spill_offset = 0;
}

static void reset_temp_regs() {
    for (int i = 0; i < NUM_TEMP_REGS; i++) temp_reg_map[i].in_use = 0;
}

static int is_number(const char *s) {
    if (!s || *s == '\0') return 0;
    char *endptr;
    strtol(s, &endptr, 10);
    return *endptr == '\0';
}

static void find_reg_for(char* reg_buf, const char* ir_temp) {
    reg_buf[0] = '\0';
    for (int i = 0; i < NUM_TEMP_REGS; i++) {
        if (temp_reg_map[i].in_use && strcmp(temp_reg_map[i].ir_temp_name, ir_temp) == 0) {
            strcpy(reg_buf, temp_reg_names[i]);
            return;
        }
    }
}

static void alloc_reg_for(char* reg_buf, FILE *out, const char* ir_temp) {
    find_reg_for(reg_buf, ir_temp);
    if (reg_buf[0] != '\0') return;

    for (int i = 0; i < NUM_TEMP_REGS; i++) {
        if (!temp_reg_map[i].in_use) {
            temp_reg_map[i].in_use = 1;
            strncpy(temp_reg_map[i].ir_temp_name, ir_temp, 31);
            strcpy(reg_buf, temp_reg_names[i]);
            return;
        }
    }

    int victim_idx = 5;
    const char* victim_ir_temp = temp_reg_map[victim_idx].ir_temp_name;
    const char* victim_reg_name = temp_reg_names[victim_idx];
    
    Var* new_spill = (Var*)malloc(sizeof(Var));
    strcpy(new_spill->ir_temp_name, victim_ir_temp);
    new_spill->offset = next_spill_offset;
    next_spill_offset += 4;
    new_spill->next = spilled_vars_head;
    spilled_vars_head = new_spill;

    fprintf(out, "  # SPILL: %s from %s to stack offset %d(sp)\n", victim_ir_temp, victim_reg_name, new_spill->offset);
    fprintf(out, "  sw %s, %d(sp)\n", victim_reg_name, new_spill->offset);

    strncpy(temp_reg_map[victim_idx].ir_temp_name, ir_temp, 31);
    strcpy(reg_buf, victim_reg_name);
}

static void load_operand_to_reg(char* reg_buf, FILE* out, const char* operand, int target_reg_idx) {
    const char* target_reg_name = temp_reg_names[target_reg_idx];
    strcpy(reg_buf, target_reg_name);

    if (is_number(operand)) {
        fprintf(out, "  li %s, %s\n", target_reg_name, operand);
        return;
    }
    
    char src_reg_buf[8];
    find_reg_for(src_reg_buf, operand);
    if (src_reg_buf[0] != '\0') {
        if (strcmp(src_reg_buf, target_reg_name) != 0) fprintf(out, "  mv %s, %s\n", target_reg_name, src_reg_buf);
    } else {
        Var* spill = spilled_vars_head;
        while(spill && strcmp(spill->ir_temp_name, operand) != 0) spill = spill->next;
        if (spill) {
            fprintf(out, "  # LOAD SPILLED: %s into %s from stack offset %d(sp)\n", operand, target_reg_name, spill->offset);
            fprintf(out, "  lw %s, %d(sp)\n", target_reg_name, spill->offset);
        } else {
            fprintf(out, "  # IR_ERROR: Variable '%s' not found. Treating as 0.\n", operand);
            fprintf(out, "  li %s, 0\n", target_reg_name);
        }
    }
}


// --- 主生成函数 (有修改) ---
void gen_riscv(const char *filename) {
    FILE *out = fopen(filename, "w");
    if (!out) { perror("Failed to open output file"); return; }

    fprintf(out, ".text\n");
    IR *current_ir = ir_head;

    while (current_ir) {
        if (current_ir->op == IR_FUNC_BEGIN) {
            const char* func_name = current_ir->a;
            int stack_size = 512; 

            fprintf(out, "\n.globl %s\n", func_name);
            fprintf(out, "%s:\n", func_name);
            fprintf(out, "  addi sp, sp, -%d\n", stack_size);
            fprintf(out, "  sw ra, %d(sp)\n", stack_size - 4);

            reset_temp_regs();
            reset_spilled_vars();
            int is_path_terminated = 0;
            int arg_count = 0;
            
            char reg_buf1[8], reg_buf2[8], reg_buf3[8];

            IR* p = current_ir->next;
            while (p && p->op != IR_FUNC_END) {
                if (is_path_terminated && p->op != IR_LABEL) {
                    p = p->next; continue;
                }

                switch (p->op) {
                    case IR_LABEL:
                        is_path_terminated = 0;
                        fprintf(out, "%s:\n", p->a);
                        break;
                    case IR_GOTO: fprintf(out, "  j %s\n", p->a); is_path_terminated = 1; break;
                    case IR_IFZ: {
                        find_reg_for(reg_buf1, p->a);
                        if (reg_buf1[0] != '\0') fprintf(out, "  beqz %s, %s\n", reg_buf1, p->b);
                        break;
                    }
                    case IR_LOADI: {
                        alloc_reg_for(reg_buf1, out, p->a);
                        fprintf(out, "  li %s, %d\n", reg_buf1, p->extra);
                        break;
                    }
                    case IR_MOVE: {
                        alloc_reg_for(reg_buf1, out, p->a); // dst
                        if (strncmp(p->b, "param", 5) == 0) {
                            int param_idx = atoi(p->b + 5);
                            if (param_idx < 8) fprintf(out, "  mv %s, a%d\n", reg_buf1, param_idx);
                        } else {
                            load_operand_to_reg(reg_buf2, out, p->b, 0); // src to t0
                            if (strcmp(reg_buf2, reg_buf1) != 0) fprintf(out, "  mv %s, %s\n", reg_buf1, reg_buf2);
                        }
                        break;
                    }
                    case IR_BIN: {
                        load_operand_to_reg(reg_buf2, out, p->b, 1); // lhs to t1
                        load_operand_to_reg(reg_buf3, out, p->c, 2); // rhs to t2
                        alloc_reg_for(reg_buf1, out, p->a);         // dst
                        
                        #define BIN_OP(op) fprintf(out, "  " #op " %s, %s, %s\n", reg_buf1, reg_buf2, reg_buf3)
                        switch((Operator)p->extra) {
                            case OP_PLUS: BIN_OP(add); break; case OP_MINUS: BIN_OP(sub); break;
                            case OP_MUL: BIN_OP(mul); break; case OP_DIV: BIN_OP(div); break;
                            case OP_MOD: BIN_OP(rem); break; case OP_LT: BIN_OP(slt); break;
                            case OP_GT: BIN_OP(sgt); break;
                            case OP_LE: fprintf(out, "  sgt %s, %s, %s\n  xori %s, %s, 1\n", reg_buf1, reg_buf2, reg_buf3, reg_buf1, reg_buf1); break;
                            case OP_GE: fprintf(out, "  slt %s, %s, %s\n  xori %s, %s, 1\n", reg_buf1, reg_buf2, reg_buf3, reg_buf1, reg_buf1); break;
                            case OP_EQ: fprintf(out, "  sub t3, %s, %s\n  seqz %s, t3\n", reg_buf2, reg_buf3, reg_buf1); break;
                            case OP_NE: fprintf(out, "  sub t3, %s, %s\n  snez %s, t3\n", reg_buf2, reg_buf3, reg_buf1); break;
                            default: break;
                        }
                        #undef BIN_OP
                        break;
                    }
                    case IR_RET: {
                        if (p->a[0] != '\0') {
                            load_operand_to_reg(reg_buf1, out, p->a, 0);
                            fprintf(out, "  mv a0, %s\n", reg_buf1);
                        } else { fprintf(out, "  li a0, 0\n"); }
                        fprintf(out, "  j %s_epilogue\n", func_name);
                        is_path_terminated = 1;
                        break;
                    }
                    case IR_ARG: { // 【逻辑修正】
                        if (arg_count < 8) {
                            // 总是加载到t6，一个不常用的临时寄存器
                            load_operand_to_reg(reg_buf1, out, p->a, 6); 
                            // 然后移动到正确的参数寄存器aX
                            fprintf(out, "  mv a%d, %s\n", arg_count, reg_buf1);
                        }
                        arg_count++;
                        break;
                    }
                    case IR_CALL: {
                        int caller_save_offset = 8;
                        for (int i = 0; i < NUM_TEMP_REGS; i++) {
                            if (temp_reg_map[i].in_use) {
                                fprintf(out, "  sw %s, %d(sp)\n", temp_reg_names[i], stack_size - caller_save_offset);
                                caller_save_offset += 4;
                            }
                        }

                        fprintf(out, "  call %s\n", p->b);

                        caller_save_offset = 8;
                        for (int i = 0; i < NUM_TEMP_REGS; i++) {
                            if (temp_reg_map[i].in_use) {
                                fprintf(out, "  lw %s, %d(sp)\n", temp_reg_names[i], stack_size - caller_save_offset);
                                caller_save_offset += 4;
                            }
                        }

                        alloc_reg_for(reg_buf1, out, p->a);
                        fprintf(out, "  mv %s, a0\n", reg_buf1);
                        arg_count = 0;
                        break;
                    }
                    default: break;
                }
                p = p->next;
            }
            
            fprintf(out, "%s_epilogue:\n", func_name);
            fprintf(out, "  lw ra, %d(sp)\n", stack_size - 4);
            fprintf(out, "  addi sp, sp, %d\n", stack_size);
            fprintf(out, "  ret\n");

            current_ir = p;
        }
        
        if (current_ir) current_ir = current_ir->next;
    }

    fclose(out);
}