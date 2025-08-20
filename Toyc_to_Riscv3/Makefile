# 编译器设置
CC = gcc
LEX = flex
YACC = bison
CFLAGS = -g -Wall -I.

# 源文件
YACC_SRC = toyc.y
LEX_SRC = toyc.l
SRCS = gen_ir.c gen_riscv.c ir.c
OBJS = $(SRCS:.c=.o)
GEN_SRCS = toyc.tab.c lex.yy.c
GEN_OBJS = $(GEN_SRCS:.c=.o)

# 可执行文件
TARGET = toyc

all: $(TARGET)

# 生成可执行文件
$(TARGET): $(GEN_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

# 生成词法分析器
lex.yy.c: $(LEX_SRC) toyc.tab.h
	$(LEX) $<

# 生成语法分析器和头文件
toyc.tab.c toyc.tab.h: $(YACC_SRC)
	$(YACC) -d $<

# 编译C文件
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS) $(GEN_OBJS) $(GEN_SRCS) toyc.tab.h

.PHONY: all clean