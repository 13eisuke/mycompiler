%{
#include "ast.h"
#include "compiler.tab.h"
#include<math.h>
%}
%%
"define" {return DEFINE;}
"array" {return ARRAY;}
"while" {return WHILE;}
"for" {return FOR;}
"if" {return IF;}
"else" {return ELSE;}
";" {yytext[0]='\0';return SEMIC;}
"[" {yytext[0]='\0';return L_BRACKET;}
"]" {yytext[0]='\0';return R_BRACKET;}
"(" {yytext[0]='\0';return L_PARAN;}
")" {yytext[0]='\0';return R_PARAN;}
"{" {yytext[0]='\0';return L_BRACE;}
"}" {yytext[0]='\0';return R_BRACE;}
"==" {yytext[0]='\0';return EQ;}
"<=" {yytext[0]='\0';return LTE;}
">=" {yytext[0]='\0';return GTE;}
"++" {yytext[0]='\0';return INC;}
"=" {yytext[0]='\0';return ASSIGN;}
"+" {yytext[0]='\0';return ADD;}
"-" {yytext[0]='\0';return SUB;}
"*" {yytext[0]='\0';return MUL;}
"/" {yytext[0]='\0';return DIV;}
"%" {yytext[0]='\0';return REM;}
"<" {yytext[0]='\0';return LT;}
">" {yytext[0]='\0';return GT;}
[0-9]+ {yylval.ival = atoi(yytext); return NUMBER;}
([a-zA-Z]+|[a-zA-Z]+[0-9]*) {yylval.sp = yytext; return IDENT;}
[\t\n ] ;
. {return yytext[0]='\0';}
%%