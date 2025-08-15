#ifndef IR_H
#define IR_H

#include "ast.h" // --- 修改：包含 ast.h 以使用 Operator 枚举
#include <stdio.h>

/*
 * --- 修改：移除自定义的 BinOp 枚举 ---
 * 我们将直接使用在 ast.h 中定义的 Operator 枚举，
 * 以避免重复定义和名称冲突。
 */

/*
 * 定义所有 IR 指令的操作码。
 */
typedef enum {
    IR_FUNC_BEGIN,   // 函数开始
    IR_FUNC_END,     // 函数结束
    IR_LABEL,        // 定义标签
    IR_GOTO,         // 无条件跳转
    IR_IFZ,          // 如果操作数为 0，则跳转
    IR_MOVE,         // 寄存器赋值: dst = src
    IR_LOADI,        // 加载立即数: dst = immediate
    IR_BIN,          // 二元运算: dst = a (op) b
    IR_RET,          // 函数返回
    IR_ARG,          // 传递函数实参
    IR_CALL          // 函数调用: dst = call func, nargs
} IROp;

/*
 * 定义单条 IR 指令的结构。
 */
typedef struct IR {
    IROp op;
    char a[32], b[32], c[32]; // 操作数 (寄存器/名字/标签)
    int  extra;               // 额外信息 (例如二元运算的操作符, 或参数个数)
    struct IR *next;          // 指向下一条指令
} IR;

/* 全局 IR 链表头指针 */
extern IR *ir_head;

/* IR 操作函数声明 */
void ir_clear(void);
void ir_emit_func_begin(const char *name);
void ir_emit_func_end(const char *name);
void ir_emit_label(const char *label);
void ir_emit_goto(const char *label);
void ir_emit_ifz(const char *reg, const char *label);
void ir_emit_move(const char *dst, const char *src);
void ir_emit_loadi(const char *dst, int imm);
/* --- 修改：ir_emit_bin 的参数类型现在是 Operator --- */
void ir_emit_bin(Operator op, const char *dst, const char *lhs, const char *rhs);
void ir_emit_ret(const char *reg);
void ir_emit_arg(const char *reg);
void ir_emit_call(const char *dst, const char *fname, int nargs);

/*
 * 打印 IR 的函数。
 * 函数名已修改为 print_ir 以匹配 toyc.y 中的调用。
 */
void print_ir(void);

#endif // IR_H
