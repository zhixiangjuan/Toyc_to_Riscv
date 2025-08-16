%{
#include "ast.h"
#include "gen_riscv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* yytext;

void yyerror(const char* s);
int yylex(void);

extern FILE *yyin;

/* AST 创建函数声明（已有实现）*/
ASTNode* create_comp_unit(ASTNode* func_def);
ASTNode* create_func_def(char* ret_type, char* func_name, ASTNode* params, ASTNode* block);
ASTNode* create_param(char* type, char* name);
ASTNode* create_block(ASTNode* stmt_list);
ASTNode* create_stmt(int type, ASTNode* expr, ASTNode* then_stmt, ASTNode* else_stmt, ASTNode* loop_stmt);
ASTNode* create_expr(int op, ASTNode* left, ASTNode* right);
ASTNode* create_primary(char* id, ASTNode* args);
ASTNode* create_id(char* name);
ASTNode* create_number(int value);

void free_ast(ASTNode* node);

/* --- 修改：包含 ir.h 来获取 print_ir 和 gen_comp_unit_ir 的声明 --- */
#include "gen_ir.h"
#include "ir.h" // <--- 在这里添加这一行

/* 保存解析出的 AST 根，供 main 使用 */
ASTNode* ast_root = NULL;
%}

/* 以下部分保持不变... */
%union {
  int num;
  char* str;
  ASTNode* node;
}

/* Token 定义 */
%token INT VOID IF ELSE WHILE BREAK CONTINUE RETURN
%token LOR LAND LT GT LE GE EQ NE
%token PLUS MINUS MUL DIV MOD NOT ASSIGN
%token SEMI COMMA LPAREN RPAREN LBRACE RBRACE
%token LBRACKET RBRACKET
%token <num> NUMBER
%token <str> ID

%left LOR
%left LAND
%left LT GT LE GE EQ NE
%left PLUS MINUS
%left MUL DIV MOD
%right UNARY

%type <str> type
%type <node> program comp_unit func_def param_list param stmt block stmt_list
%type <node> expr l_or_expr l_and_expr rel_expr add_expr mul_expr unary_expr primary_expr
%type <node> expr_list lval

%start program

%%

program:
    comp_unit { ast_root = $1; } // 修改：直接使用$1，create_comp_unit 在 comp_unit 规则中处理
    ;

comp_unit:
    func_def { $$ = create_comp_unit($1); }
    | comp_unit func_def { 
        // 正确的链接方式：将新的 func_def 添加到链表末尾
        // 为了简单起见，我们继续使用您的头插法，但在 gen_ir 中反转
        $2->next = $1->data.comp_unit.func_def;
        $$ = create_comp_unit($2);
    }
    ;

/* function definition */
func_def:
    type ID LPAREN param_list RPAREN block {
        $$ = create_func_def($1, $2, $4, $6);
    }
    ;

type:
    INT { $$ = "int"; }
    | VOID { $$ = "void"; }
    ;

param_list:
    /* empty */ { $$ = NULL; }
    | param { $$ = $1; }
    | param_list COMMA param { $3->next = $1; $$ = $3; }
    ;

param:
    INT ID { $$ = create_param("int", $2); }
    ;

lval:
    ID { $$ = create_id($1); }
    | ID LBRACKET expr RBRACKET { 
        ASTNode* idn = create_id($1);
        $$ = create_expr(OP_INDEX, idn, $3); 
    }
    ;

stmt:
    SEMI { $$ = create_stmt(STMT_EMPTY, NULL, NULL, NULL, NULL); }
    | expr SEMI { $$ = create_stmt(STMT_EXPR, $1, NULL, NULL, NULL); }
    | lval ASSIGN expr SEMI { 
        $$ = create_stmt(STMT_ASSIGN, create_expr(OP_ASSIGN, $1, $3), NULL, NULL, NULL); 
    }
    | INT ID ASSIGN expr SEMI {
        ASTNode* id_node = create_id($2);
        ASTNode* assign = create_expr(OP_ASSIGN, id_node, $4);
        $$ = create_stmt(STMT_DECL, assign, NULL, NULL, NULL);
    }
    | INT ID LBRACKET NUMBER RBRACKET SEMI {
        ASTNode* idn = create_id($2);
        ASTNode* numn = create_number($4);
        ASTNode* arr_decl_expr = create_expr(OP_INDEX, idn, numn);
        $$ = create_stmt(STMT_DECL, arr_decl_expr, NULL, NULL, NULL);
    }
    | block { $$ = $1; }
    | IF LPAREN expr RPAREN stmt %prec IF {
        $$ = create_stmt(STMT_IF, $3, $5, NULL, NULL);
    }
    | IF LPAREN expr RPAREN stmt ELSE stmt {
        $$ = create_stmt(STMT_IF, $3, $5, $7, NULL);
    }
    | WHILE LPAREN expr RPAREN stmt {
        $$ = create_stmt(STMT_WHILE, $3, $5, NULL, NULL);
    }
    | BREAK SEMI { $$ = create_stmt(STMT_BREAK, NULL, NULL, NULL, NULL); }
    | CONTINUE SEMI { $$ = create_stmt(STMT_CONTINUE, NULL, NULL, NULL, NULL); }
    | RETURN SEMI { $$ = create_stmt(STMT_RETURN, NULL, NULL, NULL, NULL); }
    | RETURN expr SEMI { $$ = create_stmt(STMT_RETURN, $2, NULL, NULL, NULL); }
    ;

block:
    LBRACE stmt_list RBRACE { $$ = create_block($2); }
    ;

stmt_list:
    /* empty */ { $$ = NULL; }
    | stmt { $$ = $1; }
    | stmt_list stmt { $2->next = $1; $$ = $2; }
    ;

expr:
    l_or_expr { $$ = $1; }
    ;

l_or_expr:
    l_and_expr { $$ = $1; }
    | l_or_expr LOR l_and_expr { $$ = create_expr(OP_LOR, $1, $3); }
    ;

l_and_expr:
    rel_expr { $$ = $1; }
    | l_and_expr LAND rel_expr { $$ = create_expr(OP_LAND, $1, $3); }
    ;

rel_expr:
    add_expr { $$ = $1; }
    | rel_expr LT add_expr { $$ = create_expr(OP_LT, $1, $3); }
    | rel_expr GT add_expr { $$ = create_expr(OP_GT, $1, $3); }
    | rel_expr LE add_expr { $$ = create_expr(OP_LE, $1, $3); }
    | rel_expr GE add_expr { $$ = create_expr(OP_GE, $1, $3); }
    | rel_expr EQ add_expr { $$ = create_expr(OP_EQ, $1, $3); }
    | rel_expr NE add_expr { $$ = create_expr(OP_NE, $1, $3); }
    ;

add_expr:
    mul_expr { $$ = $1; }
    | add_expr PLUS mul_expr { $$ = create_expr(OP_PLUS, $1, $3); }
    | add_expr MINUS mul_expr { $$ = create_expr(OP_MINUS, $1, $3); }
    ;

mul_expr:
    unary_expr { $$ = $1; }
    | mul_expr MUL unary_expr { $$ = create_expr(OP_MUL, $1, $3); }
    | mul_expr DIV unary_expr { $$ = create_expr(OP_DIV, $1, $3); }
    | mul_expr MOD unary_expr { $$ = create_expr(OP_MOD, $1, $3); }
    ;

unary_expr:
    primary_expr { $$ = $1; }
    | PLUS unary_expr %prec UNARY { $$ = create_expr(OP_PLUS, NULL, $2); }
    | MINUS unary_expr %prec UNARY { $$ = create_expr(OP_MINUS, NULL, $2); }
    | NOT unary_expr %prec UNARY { $$ = create_expr(OP_NOT, NULL, $2); }
    ;

primary_expr:
    ID { $$ = create_id($1); }
    | NUMBER { $$ = create_number($1); }
    | LPAREN expr RPAREN { $$ = $2; }
    | ID LPAREN expr_list RPAREN { $$ = create_primary($1, $3); }
    | ID LBRACKET expr RBRACKET { 
        ASTNode* idn = create_id($1);
        $$ = create_expr(OP_INDEX, idn, $3);
    }
    ;

expr_list:
    /* empty */ { $$ = NULL; }
    | expr { $$ = $1; }
    | expr_list COMMA expr { $3->next = $1; $$ = $3; }
    ;

%%

/*int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Cannot open input file");
            return 1;
        }
    } else {
        yyin = stdin;
    }

    if (yyparse() == 0 && ast_root) {
        gen_comp_unit_ir(ast_root);
        print_ir(); // 现在编译器知道这个函数了
        free_ast(ast_root);
        free_ir();
    }

    if (yyin != stdin) fclose(yyin);
    return 0;
}*/

void yyerror(const char* s) {
    fprintf(stderr, "Syntax error: %s near token '%s'\n", s, yytext);
}

/* AST 节点创建函数实现 (这部分保持不变) */
ASTNode* create_comp_unit(ASTNode* func_def) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_COMP_UNIT;
  node->data.comp_unit.func_def = func_def;
  node->next = NULL;
  return node;
}

ASTNode* create_func_def(char* ret_type, char* func_name, ASTNode* params, ASTNode* block) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_FUNC_DEF;
  node->data.func_def.ret_type = strdup(ret_type);
  node->data.func_def.func_name = strdup(func_name);
  node->data.func_def.params = params;
  node->data.func_def.block = block;
  node->next = NULL;
  return node;
}

ASTNode* create_param(char* type, char* name) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_PARAM;
  node->data.param.type = strdup(type);
  node->data.param.name = strdup(name);
  node->next = NULL;
  return node;
}

ASTNode* create_block(ASTNode* stmt_list) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_BLOCK;
  node->data.block.stmt_list = stmt_list;
  node->next = NULL;
  return node;
}

ASTNode* create_stmt(int stmt_type, ASTNode* expr, ASTNode* then_stmt, ASTNode* else_stmt, ASTNode* loop_stmt) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_STMT;
  node->data.stmt.stmt_type = stmt_type;
  node->data.stmt.expr = expr;
  node->data.stmt.then_stmt = then_stmt;
  node->data.stmt.else_stmt = else_stmt;
  node->data.stmt.loop_stmt = loop_stmt;
  node->next = NULL;
  return node;
}

ASTNode* create_expr(int op, ASTNode* left, ASTNode* right) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_EXPR;
  node->data.expr.op = op;
  node->data.expr.left = left;
  node->data.expr.right = right;
  node->next = NULL;
  return node;
}

ASTNode* create_primary(char* id, ASTNode* args) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_PRIMARY;
  node->data.primary.id = strdup(id);
  node->data.primary.args = args;
  node->next = NULL;
  return node;
}

ASTNode* create_id(char* name) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_ID;
  node->data.id = strdup(name);
  node->next = NULL;
  return node;
}

ASTNode* create_number(int value) {
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NODE_NUMBER;
  node->data.number = value;
  node->next = NULL;
  return node;
}

void free_ast(ASTNode* node) {
  if (!node) return;

  // ... (free_ast 实现保持不变) ...
  switch (node->type) {
    case NODE_FUNC_DEF:
      free(node->data.func_def.ret_type);
      free(node->data.func_def.func_name);
      free_ast(node->data.func_def.params);
      free_ast(node->data.func_def.block);
      break;
    case NODE_PARAM:
      free(node->data.param.type);
      free(node->data.param.name);
      break;
    case NODE_BLOCK:
      free_ast(node->data.block.stmt_list);
      break;
    case NODE_STMT:
      free_ast(node->data.stmt.expr);
      free_ast(node->data.stmt.then_stmt);
      free_ast(node->data.stmt.else_stmt);
      free_ast(node->data.stmt.loop_stmt);
      break;
    case NODE_EXPR:
      free_ast(node->data.expr.left);
      free_ast(node->data.expr.right);
      break;
    case NODE_PRIMARY:
      free(node->data.primary.id);
      free_ast(node->data.primary.args);
      break;
    case NODE_ID:
      free(node->data.id);
      break;
    case NODE_COMP_UNIT:
      free_ast(node->data.comp_unit.func_def);
      break;
    default:
      break;
  }
  free_ast(node->next);
  free(node);
}

int main(int argc, char** argv) {
    //printf("--- CHECKPOINT: Main function started. ---\n"); // <-- 检查点 1

    /*if (argc <= 1) {
        fprintf(stderr, "Usage: %s <input_file.tc>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Cannot open input file");
        return 1;
    }*/

    yyin=stdin;

    //printf("--- CHECKPOINT: Calling yyparse() now... ---\n"); // <-- 检查点 2
    int parse_result = yyparse();
    //printf("--- CHECKPOINT: yyparse() finished with code: %d ---\n", parse_result); // <-- 检查点 3

    if (parse_result != 0 || !ast_root) {
        fprintf(stderr, "Error: Parsing failed or AST root is null. Aborting.\n");
        if (yyin != stdin) fclose(yyin);
        return 1;
    }

    //printf("--- CHECKPOINT: AST created successfully. Generating IR... ---\n"); // <-- 检查点 4

    gen_comp_unit_ir(ast_root);

    //printf("--- CHECKPOINT: IR generated. Printing IR for debug... ---\n"); // <-- 检查点 5
    //print_ir();

    char output_filename[256];
    strncpy(output_filename, argv[1], sizeof(output_filename) - 1);
    output_filename[sizeof(output_filename) - 1] = '\0';
    char* dot = strrchr(output_filename, '.');
    if (dot) { strcpy(dot, ".s"); }
    else { strncat(output_filename, ".s", sizeof(output_filename) - strlen(output_filename) - 1); }

    //printf("--- CHECKPOINT: Generating RISC-V code to %s... ---\n", output_filename); // <-- 检查点 6
    gen_riscv(output_filename);

    //printf("--- CHECKPOINT: RISC-V generation complete. Cleaning up... ---\n"); // <-- 检查点 7

    free_ast(ast_root);
    free_ir();

    if (yyin != stdin) fclose(yyin);
    //printf("--- CHECKPOINT: Program finished successfully. ---\n"); // <-- 检查点 8

    FILE* file = std::fopen("output.s", "r");
    if (!file) {
        std::perror("Error opening file");
        return 1;
    }

    int ch;
    while ((ch = std::fgetc(file)) != EOF) {
        std::putchar(ch);  // 将字符输出到 stdout
    }

    std::fclose(file);

    return 0;
}
