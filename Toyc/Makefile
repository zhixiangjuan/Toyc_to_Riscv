compiler: lex.yy.o toyc.tab.o ir.o gen_ir.o gen_riscv.o
    gcc lex.yy.o toyc.tab.o ir.o gen_ir.o gen_riscv.o -o compiler

lex.yy.o: lex.yy.c
    gcc lex.yy.c -c -o lex.yy.o

toyc.tab.o: toyc.tab.c
    gcc toyc.tab.c -c -o toyc.tab.o

ir.o: ir.c
    gcc ir.c -c -o ir.o

gen_ir.o: gen_ir.c
    gcc gen_ir.c -c -o gen_ir.o

gen_riscv.o: gen_riscv.c
    gcc gen_riscv.c -c -o gen_riscv.o

lex.yy.c: toyc.l
    flex toyc.l

toyc.tab.c: toyc.y
    bison -d -o toyc.tab.c toyc.y