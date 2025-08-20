#ifndef AST_H
#define AST_H

typedef enum {
    NODE_COMP_UNIT,
    NODE_FUNC_DEF,
    NODE_PARAM,
    NODE_BLOCK,
    NODE_STMT,
    NODE_EXPR,
    NODE_PRIMARY,
    NODE_ID,
    NODE_NUMBER
} NodeType;

typedef enum {
    STMT_EMPTY,
    STMT_EXPR,
    STMT_ASSIGN,
    STMT_DECL,
    STMT_IF,
    STMT_WHILE,
    STMT_BREAK,
    STMT_CONTINUE,
    STMT_RETURN
} StmtType;

typedef enum {
    OP_LOR, OP_LAND,
    OP_LT, OP_GT, OP_LE, OP_GE, OP_EQ, OP_NE,
    OP_PLUS, OP_MINUS,
    OP_MUL, OP_DIV, OP_MOD,
    OP_NOT, OP_ASSIGN,
    OP_INDEX  /* 新增：数组下标操作 a[expr] 用这个 op 表示，left = id, right = index expr */
} Operator;

typedef struct ASTNode {
    NodeType type;
    struct ASTNode* next;

    union {
        struct {
            struct ASTNode* func_def;
        } comp_unit;

        struct {
            char* ret_type;
            char* func_name;
            struct ASTNode* params;
            struct ASTNode* block;
        } func_def;

        struct {
            char* type;
            char* name;
        } param;

        struct {
            struct ASTNode* stmt_list;
        } block;

        struct {
            StmtType stmt_type;
            struct ASTNode* expr;
            struct ASTNode* then_stmt;
            struct ASTNode* else_stmt;
            struct ASTNode* loop_stmt;
        } stmt;

        struct {
            int op; /* 使用 Operator 枚举 */
            struct ASTNode* left;
            struct ASTNode* right;
        } expr;

        struct {
            char* id;
            struct ASTNode* args;
        } primary;

        char* id;
        int number;
    } data;
} ASTNode;

/* 创建函数（你原来有的接口，这里声明） */
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

#endif // AST_H

