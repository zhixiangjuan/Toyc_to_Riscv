#ifndef GEN_IR_H
#define GEN_IR_H
#include "ast.h"

void gen_comp_unit_ir(ASTNode *root);
void free_ir(void); // 如果你需要清理，可直接调用 ir_clear()

#endif

