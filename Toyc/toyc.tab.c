
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "toyc.y"

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


/* Line 189 of yacc.c  */
#line 109 "toyc.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     VOID = 259,
     IF = 260,
     ELSE = 261,
     WHILE = 262,
     BREAK = 263,
     CONTINUE = 264,
     RETURN = 265,
     LOR = 266,
     LAND = 267,
     LT = 268,
     GT = 269,
     LE = 270,
     GE = 271,
     EQ = 272,
     NE = 273,
     PLUS = 274,
     MINUS = 275,
     MUL = 276,
     DIV = 277,
     MOD = 278,
     NOT = 279,
     ASSIGN = 280,
     SEMI = 281,
     COMMA = 282,
     LPAREN = 283,
     RPAREN = 284,
     LBRACE = 285,
     RBRACE = 286,
     LBRACKET = 287,
     RBRACKET = 288,
     NUMBER = 289,
     ID = 290,
     UNARY = 291
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 37 "toyc.y"

  int num;
  char* str;
  ASTNode* node;



/* Line 214 of yacc.c  */
#line 189 "toyc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 201 "toyc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   134

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  118

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    17,    19,    21,    22,
      24,    28,    31,    33,    38,    40,    43,    48,    54,    61,
      63,    69,    77,    83,    86,    89,    92,    96,   100,   101,
     103,   106,   108,   110,   114,   116,   120,   122,   126,   130,
     134,   138,   142,   146,   148,   152,   156,   158,   162,   166,
     170,   172,   175,   178,   181,   183,   185,   189,   194,   199,
     200,   202
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      38,     0,    -1,    39,    -1,    40,    -1,    39,    40,    -1,
      41,    35,    28,    42,    29,    46,    -1,     3,    -1,     4,
      -1,    -1,    43,    -1,    42,    27,    43,    -1,     3,    35,
      -1,    35,    -1,    35,    32,    48,    33,    -1,    26,    -1,
      48,    26,    -1,    44,    25,    48,    26,    -1,     3,    35,
      25,    48,    26,    -1,     3,    35,    32,    34,    33,    26,
      -1,    46,    -1,     5,    28,    48,    29,    45,    -1,     5,
      28,    48,    29,    45,     6,    45,    -1,     7,    28,    48,
      29,    45,    -1,     8,    26,    -1,     9,    26,    -1,    10,
      26,    -1,    10,    48,    26,    -1,    30,    47,    31,    -1,
      -1,    45,    -1,    47,    45,    -1,    49,    -1,    50,    -1,
      49,    11,    50,    -1,    51,    -1,    50,    12,    51,    -1,
      52,    -1,    51,    13,    52,    -1,    51,    14,    52,    -1,
      51,    15,    52,    -1,    51,    16,    52,    -1,    51,    17,
      52,    -1,    51,    18,    52,    -1,    53,    -1,    52,    19,
      53,    -1,    52,    20,    53,    -1,    54,    -1,    53,    21,
      54,    -1,    53,    22,    54,    -1,    53,    23,    54,    -1,
      55,    -1,    19,    54,    -1,    20,    54,    -1,    24,    54,
      -1,    35,    -1,    34,    -1,    28,    48,    29,    -1,    35,
      28,    56,    29,    -1,    35,    32,    48,    33,    -1,    -1,
      48,    -1,    56,    27,    48,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    69,    69,    73,    74,    84,    90,    91,    95,    96,
      97,   101,   105,   106,   113,   114,   115,   118,   123,   129,
     130,   133,   136,   139,   140,   141,   142,   146,   150,   151,
     152,   156,   160,   161,   165,   166,   170,   171,   172,   173,
     174,   175,   176,   180,   181,   182,   186,   187,   188,   189,
     193,   194,   195,   196,   200,   201,   202,   203,   204,   211,
     212,   213
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "VOID", "IF", "ELSE", "WHILE",
  "BREAK", "CONTINUE", "RETURN", "LOR", "LAND", "LT", "GT", "LE", "GE",
  "EQ", "NE", "PLUS", "MINUS", "MUL", "DIV", "MOD", "NOT", "ASSIGN",
  "SEMI", "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "NUMBER", "ID", "UNARY", "$accept", "program", "comp_unit",
  "func_def", "type", "param_list", "param", "lval", "stmt", "block",
  "stmt_list", "expr", "l_or_expr", "l_and_expr", "rel_expr", "add_expr",
  "mul_expr", "unary_expr", "primary_expr", "expr_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    41,    41,    42,    42,
      42,    43,    44,    44,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    46,    47,    47,
      47,    48,    49,    49,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    52,    53,    53,    53,    53,
      54,    54,    54,    54,    55,    55,    55,    55,    55,    56,
      56,    56
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     6,     1,     1,     0,     1,
       3,     2,     1,     4,     1,     2,     4,     5,     6,     1,
       5,     7,     5,     2,     2,     2,     3,     3,     0,     1,
       2,     1,     1,     3,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     2,     1,     1,     3,     4,     4,     0,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,     7,     0,     2,     3,     0,     1,     4,     0,
       8,     0,     0,     9,    11,     0,     0,    10,    28,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,    55,    54,     0,    29,    19,     0,     0,    31,    32,
      34,    36,    43,    46,    50,     0,     0,     0,    23,    24,
      25,    54,     0,    51,    52,    53,     0,    59,     0,     0,
      27,    30,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    56,    60,     0,     0,     0,    33,    35,    37,
      38,    39,    40,    41,    42,    44,    45,    47,    48,    49,
       0,     0,     0,     0,     0,     0,    57,    58,    16,    17,
       0,    20,    22,    58,    61,    18,     0,    21
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,    13,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -36
static const yytype_int8 yypact[] =
{
      40,   -36,   -36,    15,    40,   -36,    13,   -36,   -36,   -11,
      26,    30,     9,   -36,   -36,    26,    24,   -36,    99,   -36,
      31,    22,    42,    46,    53,    11,   -16,   -16,   -16,   -36,
     -16,   -36,   -12,    57,   -36,   -36,    66,    58,    72,    75,
      10,    33,    19,   -36,   -36,   -18,   -16,   -16,   -36,   -36,
     -36,   -26,    62,   -36,   -36,   -36,    60,   -16,   -16,   -16,
     -36,   -36,   -36,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,    59,    69,    70,
     -16,   -36,   -36,   -36,    20,    77,    65,    75,    10,    33,
      33,    33,    33,    33,    33,    19,    19,   -36,   -36,   -36,
      79,    78,    99,    99,    80,   -16,   -36,    87,   -36,   -36,
      88,    89,   -36,   -36,   -36,   -36,    99,   -36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -36,   -36,   -36,   111,   -36,   -36,   101,   -36,   -35,   104,
     -36,   -25,   -36,    54,    39,    -6,     6,   -17,   -36,   -36
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -14
static const yytype_int8 yytable[] =
{
      52,    61,    57,    26,    27,    56,    80,    76,    28,    53,
      54,    55,    30,   -12,    77,     7,    57,    10,    31,    51,
      58,    78,    79,    65,    66,    67,    68,    69,    70,    11,
      26,    27,    83,    85,    86,    28,    15,    50,    16,    30,
      73,    74,    75,     1,     2,    31,    51,   105,     9,   106,
      46,   100,    71,    72,    18,   104,    97,    98,    99,    89,
      90,    91,    92,    93,    94,    14,    45,   111,   112,    20,
      47,    21,    48,    22,    23,    24,    25,    95,    96,    49,
     114,   117,    59,    63,    62,    26,    27,    64,    81,    82,
      28,   108,    29,   101,    30,   116,    18,    60,   102,   103,
      31,    32,    20,    88,    21,   109,    22,    23,    24,    25,
     107,   110,   -13,   113,   115,     8,    17,    87,    26,    27,
      19,     0,     0,    28,     0,    29,     0,    30,     0,    18,
       0,     0,     0,    31,    32
};

static const yytype_int8 yycheck[] =
{
      25,    36,    28,    19,    20,    30,    32,    25,    24,    26,
      27,    28,    28,    25,    32,     0,    28,    28,    34,    35,
      32,    46,    47,    13,    14,    15,    16,    17,    18,     3,
      19,    20,    57,    58,    59,    24,    27,    26,    29,    28,
      21,    22,    23,     3,     4,    34,    35,    27,    35,    29,
      28,    76,    19,    20,    30,    80,    73,    74,    75,    65,
      66,    67,    68,    69,    70,    35,    35,   102,   103,     3,
      28,     5,    26,     7,     8,     9,    10,    71,    72,    26,
     105,   116,    25,    11,    26,    19,    20,    12,    26,    29,
      24,    26,    26,    34,    28,     6,    30,    31,    29,    29,
      34,    35,     3,    64,     5,    26,     7,     8,     9,    10,
      33,    33,    25,    33,    26,     4,    15,    63,    19,    20,
      16,    -1,    -1,    24,    -1,    26,    -1,    28,    -1,    30,
      -1,    -1,    -1,    34,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    38,    39,    40,    41,     0,    40,    35,
      28,     3,    42,    43,    35,    27,    29,    43,    30,    46,
       3,     5,     7,     8,     9,    10,    19,    20,    24,    26,
      28,    34,    35,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    35,    28,    28,    26,    26,
      26,    35,    48,    54,    54,    54,    48,    28,    32,    25,
      31,    45,    26,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    25,    32,    48,    48,
      32,    26,    29,    48,    56,    48,    48,    50,    51,    52,
      52,    52,    52,    52,    52,    53,    53,    54,    54,    54,
      48,    34,    29,    29,    48,    27,    29,    33,    26,    26,
      33,    45,    45,    33,    48,    26,     6,    45
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 69 "toyc.y"
    { ast_root = (yyvsp[(1) - (1)].node); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 73 "toyc.y"
    { (yyval.node) = create_comp_unit((yyvsp[(1) - (1)].node)); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 74 "toyc.y"
    { 
        // 正确的链接方式：将新的 func_def 添加到链表末尾
        // 为了简单起见，我们继续使用您的头插法，但在 gen_ir 中反转
        (yyvsp[(2) - (2)].node)->next = (yyvsp[(1) - (2)].node)->data.comp_unit.func_def;
        (yyval.node) = create_comp_unit((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 84 "toyc.y"
    {
        (yyval.node) = create_func_def((yyvsp[(1) - (6)].str), (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].node), (yyvsp[(6) - (6)].node));
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 90 "toyc.y"
    { (yyval.str) = "int"; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 91 "toyc.y"
    { (yyval.str) = "void"; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 95 "toyc.y"
    { (yyval.node) = NULL; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 96 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 97 "toyc.y"
    { (yyvsp[(3) - (3)].node)->next = (yyvsp[(1) - (3)].node); (yyval.node) = (yyvsp[(3) - (3)].node); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 101 "toyc.y"
    { (yyval.node) = create_param("int", (yyvsp[(2) - (2)].str)); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 105 "toyc.y"
    { (yyval.node) = create_id((yyvsp[(1) - (1)].str)); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 106 "toyc.y"
    { 
        ASTNode* idn = create_id((yyvsp[(1) - (4)].str));
        (yyval.node) = create_expr(OP_INDEX, idn, (yyvsp[(3) - (4)].node)); 
    ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 113 "toyc.y"
    { (yyval.node) = create_stmt(STMT_EMPTY, NULL, NULL, NULL, NULL); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 114 "toyc.y"
    { (yyval.node) = create_stmt(STMT_EXPR, (yyvsp[(1) - (2)].node), NULL, NULL, NULL); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 115 "toyc.y"
    { 
        (yyval.node) = create_stmt(STMT_ASSIGN, create_expr(OP_ASSIGN, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node)), NULL, NULL, NULL); 
    ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 118 "toyc.y"
    {
        ASTNode* id_node = create_id((yyvsp[(2) - (5)].str));
        ASTNode* assign = create_expr(OP_ASSIGN, id_node, (yyvsp[(4) - (5)].node));
        (yyval.node) = create_stmt(STMT_DECL, assign, NULL, NULL, NULL);
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 123 "toyc.y"
    {
        ASTNode* idn = create_id((yyvsp[(2) - (6)].str));
        ASTNode* numn = create_number((yyvsp[(4) - (6)].num));
        ASTNode* arr_decl_expr = create_expr(OP_INDEX, idn, numn);
        (yyval.node) = create_stmt(STMT_DECL, arr_decl_expr, NULL, NULL, NULL);
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 129 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 130 "toyc.y"
    {
        (yyval.node) = create_stmt(STMT_IF, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL, NULL);
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 133 "toyc.y"
    {
        (yyval.node) = create_stmt(STMT_IF, (yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), NULL);
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 136 "toyc.y"
    {
        (yyval.node) = create_stmt(STMT_WHILE, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL, NULL);
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 139 "toyc.y"
    { (yyval.node) = create_stmt(STMT_BREAK, NULL, NULL, NULL, NULL); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 140 "toyc.y"
    { (yyval.node) = create_stmt(STMT_CONTINUE, NULL, NULL, NULL, NULL); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 141 "toyc.y"
    { (yyval.node) = create_stmt(STMT_RETURN, NULL, NULL, NULL, NULL); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 142 "toyc.y"
    { (yyval.node) = create_stmt(STMT_RETURN, (yyvsp[(2) - (3)].node), NULL, NULL, NULL); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 146 "toyc.y"
    { (yyval.node) = create_block((yyvsp[(2) - (3)].node)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 150 "toyc.y"
    { (yyval.node) = NULL; ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 151 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 152 "toyc.y"
    { (yyvsp[(2) - (2)].node)->next = (yyvsp[(1) - (2)].node); (yyval.node) = (yyvsp[(2) - (2)].node); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 156 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 160 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 161 "toyc.y"
    { (yyval.node) = create_expr(OP_LOR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 165 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 166 "toyc.y"
    { (yyval.node) = create_expr(OP_LAND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 170 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 171 "toyc.y"
    { (yyval.node) = create_expr(OP_LT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 172 "toyc.y"
    { (yyval.node) = create_expr(OP_GT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 173 "toyc.y"
    { (yyval.node) = create_expr(OP_LE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 174 "toyc.y"
    { (yyval.node) = create_expr(OP_GE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 175 "toyc.y"
    { (yyval.node) = create_expr(OP_EQ, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 176 "toyc.y"
    { (yyval.node) = create_expr(OP_NE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 180 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 181 "toyc.y"
    { (yyval.node) = create_expr(OP_PLUS, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 182 "toyc.y"
    { (yyval.node) = create_expr(OP_MINUS, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 186 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 187 "toyc.y"
    { (yyval.node) = create_expr(OP_MUL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 188 "toyc.y"
    { (yyval.node) = create_expr(OP_DIV, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 189 "toyc.y"
    { (yyval.node) = create_expr(OP_MOD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 193 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 194 "toyc.y"
    { (yyval.node) = create_expr(OP_PLUS, NULL, (yyvsp[(2) - (2)].node)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 195 "toyc.y"
    { (yyval.node) = create_expr(OP_MINUS, NULL, (yyvsp[(2) - (2)].node)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 196 "toyc.y"
    { (yyval.node) = create_expr(OP_NOT, NULL, (yyvsp[(2) - (2)].node)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 200 "toyc.y"
    { (yyval.node) = create_id((yyvsp[(1) - (1)].str)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 201 "toyc.y"
    { (yyval.node) = create_number((yyvsp[(1) - (1)].num)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 202 "toyc.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 203 "toyc.y"
    { (yyval.node) = create_primary((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 204 "toyc.y"
    { 
        ASTNode* idn = create_id((yyvsp[(1) - (4)].str));
        (yyval.node) = create_expr(OP_INDEX, idn, (yyvsp[(3) - (4)].node));
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 211 "toyc.y"
    { (yyval.node) = NULL; ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 212 "toyc.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 213 "toyc.y"
    { (yyvsp[(3) - (3)].node)->next = (yyvsp[(1) - (3)].node); (yyval.node) = (yyvsp[(3) - (3)].node); ;}
    break;



/* Line 1455 of yacc.c  */
#line 1946 "toyc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 216 "toyc.y"


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

    FILE* file = fopen(output_filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);  // 将字符输出到 stdout
    }

    fclose(file);

    return 0;
}

