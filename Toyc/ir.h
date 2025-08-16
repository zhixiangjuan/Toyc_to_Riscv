#ifndef IR_H
#define IR_H

#include "ast.h" // --- �޸ģ����� ast.h ��ʹ�� Operator ö��
#include <stdio.h>

/*
 * --- �޸ģ��Ƴ��Զ���� BinOp ö�� ---
 * ���ǽ�ֱ��ʹ���� ast.h �ж���� Operator ö�٣�
 * �Ա����ظ���������Ƴ�ͻ��
 */

/*
 * �������� IR ָ��Ĳ����롣
 */
typedef enum {
    IR_FUNC_BEGIN,   // ������ʼ
    IR_FUNC_END,     // ��������
    IR_LABEL,        // �����ǩ
    IR_GOTO,         // ��������ת
    IR_IFZ,          // ���������Ϊ 0������ת
    IR_MOVE,         // �Ĵ�����ֵ: dst = src
    IR_LOADI,        // ����������: dst = immediate
    IR_BIN,          // ��Ԫ����: dst = a (op) b
    IR_RET,          // ��������
    IR_ARG,          // ���ݺ���ʵ��
    IR_CALL          // ��������: dst = call func, nargs
} IROp;

/*
 * ���嵥�� IR ָ��Ľṹ��
 */
typedef struct IR {
    IROp op;
    char a[32], b[32], c[32]; // ������ (�Ĵ���/����/��ǩ)
    int  extra;               // ������Ϣ (�����Ԫ����Ĳ�����, ���������)
    struct IR *next;          // ָ����һ��ָ��
} IR;

/* ȫ�� IR ����ͷָ�� */
extern IR *ir_head;

/* IR ������������ */
void ir_clear(void);
void ir_emit_func_begin(const char *name);
void ir_emit_func_end(const char *name);
void ir_emit_label(const char *label);
void ir_emit_goto(const char *label);
void ir_emit_ifz(const char *reg, const char *label);
void ir_emit_move(const char *dst, const char *src);
void ir_emit_loadi(const char *dst, int imm);
/* --- �޸ģ�ir_emit_bin �Ĳ������������� Operator --- */
void ir_emit_bin(Operator op, const char *dst, const char *lhs, const char *rhs);
void ir_emit_ret(const char *reg);
void ir_emit_arg(const char *reg);
void ir_emit_call(const char *dst, const char *fname, int nargs);

/*
 * ��ӡ IR �ĺ�����
 * ���������޸�Ϊ print_ir ��ƥ�� toyc.y �еĵ��á�
 */
void print_ir(void);

#endif // IR_H
