#ifndef GEN_IR_H
#define GEN_IR_H
#include "ast.h"

void gen_comp_unit_ir(ASTNode *root);
void free_ir(void); // �������Ҫ������ֱ�ӵ��� ir_clear()

#endif

