/* gen_riscv.h */
#ifndef GEN_RISCV_H
#define GEN_RISCV_H

#include <stdio.h>

/* 将内存中的 IR 列表生成为 RISC-V32 汇编，输出到指定文件 */
void gen_riscv(FILE* out);

#endif /* GEN_RISCV_H */