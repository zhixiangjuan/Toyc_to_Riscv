%{
#include "ast.h"
#include "toyc.tab.h"
#include <stdlib.h>
#include <string.h>

extern void yyerror(const char* s);
%}

%option noyywrap nounput

DIGIT       [0-9]
ID          [a-zA-Z_][a-zA-Z0-9_]*
INTEGER     {DIGIT}+
WHITESPACE  [ \t\r\n]

%%

"int"       { return INT; }
"void"      { return VOID; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"return"    { return RETURN; }

"||"        { return LOR; }
"&&"        { return LAND; }
"<="        { return LE; }
">="        { return GE; }
"=="        { return EQ; }
"!="        { return NE; }
"<"         { return LT; }
">"         { return GT; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"%"         { return MOD; }
"!"         { return NOT; }
"="         { return ASSIGN; }

";"         { return SEMI; }
","         { return COMMA; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
"["         { return LBRACKET; }
"]"         { return RBRACKET; }

{INTEGER}   { yylval.num = atoi(yytext); return NUMBER; }
{ID}        { yylval.str = strdup(yytext); return ID; }

{WHITESPACE}+  { /* skip */ }

"//".*      { /* line comment */ }
"/*"        { 
              int c, last = 0;
              while((c = input()) != 0) {
                if(last == '*' && c == '/') break;
                last = c;
              }
            }

.           { 
              fprintf(stderr, "Lexical error: Unexpected character '%c'\n", *yytext); 
              yyerror("Invalid character");
            }

%%

