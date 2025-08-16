/* gen_riscv.h */
#ifndef GEN_RISCV_H
#define GEN_RISCV_H

/* 将内存中的 IR 列表生成为 RISC-V32 汇编，输出到指定文件 */
void gen_riscv(const char* filename);

#endif /* GEN_RISCV_H */