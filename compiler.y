%{
#include <stdio.h>
#include "ast.h"
#include "compiler.tab.h"
  extern int yylex();
  extern int yyerror();
  int sim_count = 0;
  %}

%union{
  Node* np;
  int ival;
  char* sp;
 }

%token DEFINE ARRAY WHILE FOR IF ELSE
%token SEMIC L_BRACKET R_BRACKET L_PARAN R_PARAN
%token L_BRACE R_BRACE ASSIGN
%token ADD SUB MUL DIV REM
%token EQ LT GT LTE GTE INC
%token <sp> IDENT
%token <ival> NUMBER
%type <np> program declarations decl_statement statements
%type <np> statement assignment_stmt expression term factor
%type <np> loop_stmt forassignment_stmt cond_stmt var condition ident
%%

program : declarations statements {$$ = build_node2(PROGRAM_AST, $1, $2); print_code($$); printNodes($$, 0);}

;

declarations : decl_statement declarations  {$$ = build_node2(DECLARATIONS_AST, $1, $2);}
|              decl_statement {$$ = build_node1(DECLARATIONS_AST, $1);}
;

decl_statement : DEFINE IDENT SEMIC {$$ = build_ident_node(DEFINE_AST, $2);}
|                ARRAY IDENT L_BRACKET NUMBER R_BRACKET SEMIC {$$ = build_array1_node(ARRAY1_AST, $2, $4);}
|                ARRAY IDENT L_BRACKET NUMBER R_BRACKET L_BRACKET NUMBER R_BRACKET SEMIC {$$ = build_array2_node(ARRAY2_AST, $2, $4, $7);}
;

statements : statement statements {$$ = build_node2(STATEMENTS_AST, $1, $2);}
|            statement {$$ = $1;}
;

statement : assignment_stmt {$$ = $1;}
|           loop_stmt {$$ = $1;}
|           cond_stmt {$$ = $1;}
;

assignment_stmt : ident ASSIGN expression SEMIC {$$ = build_node2(ASSIGN_AST, $1, $3);}
|                 ident L_BRACKET var R_BRACKET ASSIGN expression SEMIC {$$ = build_node3(ASSIGN_AST, $1, $3, $6);}
|                 ident L_BRACKET var R_BRACKET L_BRACKET var R_BRACKET ASSIGN expression SEMIC {$$ = build_node4(ASSIGN_AST, $1, $3, $6, $9);}
//|                 var INC SEMIC {$$ = build_node2(ASSIGNMENT_STMT_AST, $1);}
;

expression : expression ADD term {$$ = build_node2(ADD_AST, $1, $3);}
|            expression SUB term {$$ = build_node2(SUB_AST, $1, $3);}
|            term {$$ = $1;}
;


term : term MUL factor {$$ = build_node2(MUL_AST, $1, $3);}
|      term DIV factor {$$ = build_node2(DIV_AST, $1, $3);}
|      term REM factor {$$ = build_node2(REM_AST, $1, $3);}
|      factor {$$ = $1;}
;


factor : var {$$ = $1;}
|        L_PARAN expression R_PARAN {$$ = $2;}
;

var : IDENT {$$ = build_ident_node(IDENT_AST, $1);}
|     NUMBER {$$ = build_num_node(NUM_AST, $1);}
|     ident L_BRACKET var R_BRACKET {$$ = build_node2(ARRAY1_AST, $1, $3);}
|     ident L_BRACKET var R_BRACKET L_BRACKET var R_BRACKET {$$ = build_node3(ARRAY2_AST, $1, $3, $6);};

loop_stmt : WHILE L_PARAN condition R_PARAN L_BRACE statements R_BRACE {$$ = build_node2(WHILE_AST, $3, $6);}
|           FOR L_PARAN assignment_stmt condition SEMIC forassignment_stmt R_PARAN L_BRACE statements R_BRACE {$$ = build_node4(FOR_AST, $3, $4, $6, $9);}
;

forassignment_stmt : ident ASSIGN expression {$$ = build_node2(ASSIGN_AST,$1,$3);}
                   | ident L_BRACKET var R_BRACKET L_BRACKET var R_BRACKET ASSIGN expression {$$ = build_node4(ASSIGN_AST,$1,$3,$6,$9);}
                   | ident L_BRACKET var R_BRACKET ASSIGN expression {$$ = build_node3(ASSIGN_AST,$1,$3,$6);}
//                   | var INC
;

ident : IDENT {$$ = build_ident_node(IDENT_AST, $1);}

cond_stmt : IF L_PARAN condition R_PARAN L_BRACE statements R_BRACE {$$ = build_node2(IF_AST, $3, $6);}
|           IF L_PARAN condition R_PARAN L_BRACE statements R_BRACE ELSE cond_stmt {$$ = build_node3(IF_AST, $3, $6, $9);}
|           IF L_PARAN condition R_PARAN L_BRACE statements R_BRACE ELSE L_BRACE statements R_BRACE {$$ = build_node3(IF_AST, $3, $6, $10);}
;


condition : expression EQ expression {$$ = build_node2(EQ_AST, $1, $3);}
|           expression LT expression {$$ = build_node2(LT_AST, $1, $3);}
|           expression GT expression {$$ = build_node2(GT_AST, $1, $3);}
|           expression LTE expression {$$ = build_node2(LTE_AST, $1, $3);}
|           expression GTE expression {$$ = build_node2(GTE_AST, $1, $3);}
;
%%

void print_code(Node *p){
  int i;

  fprintf(fp,"\tINITIAL_GP = 0x10008000\n");
  fprintf(fp,"\tINITIAL_SP = 0x7ffffffc\n");
  fprintf(fp,"\t# system call service number\n\tstop_service = 99\n");

  // テキストセグメントの出力
  fprintf(fp,".text\n");
  fprintf(fp,"init:\n");
  fprintf(fp,"\t# initialize $gp (global pointer) and $sp (stack pointer)\n");
  fprintf(fp,"\tla      $gp, INITIAL_GP\n");
  fprintf(fp,"\tla      $sp, INITIAL_SP\n");
  fprintf(fp,"\tjal     main                    # jump to `main'\n");
  fprintf(fp,"\tnop                             #   (delay slot)\n");
  fprintf(fp,"\tli      $v0, stop_service       # $v0 <- 99 (stop_service)\n");
  fprintf(fp,"\tsyscall                         # stop\n");
  fprintf(fp,"\tnop\n");
  fprintf(fp,"\t# not reach here\n");

  fprintf(fp,"stop:\n");
  fprintf(fp,"\tj stop\n");
  fprintf(fp,"\tnop\n");
  fprintf(fp,"\n.text\t0x00001000\n\n");

  fprintf(fp, "main:\n");

  codegen(p); //コードの生成

  fprintf(fp, "\tjr\t$ra\n");

  // データセグメントの出力
  fprintf(fp,"\n.data\t0x10004000\n");
  for (i = 0; i < sim_count; i++){
    fprintf(fp, "_%s:\t.word\t0x0000\n", simTable[i].name);
  }
  fprintf(fp,"\n# End of file\n");
}


int main(int argc, char* argv[])
{

  fp = fopen(argv[1],"w");
  fprintf(fp,"# codegen:%s\n\n", argv[1]);

  if (yyparse()) {
    fprintf(stderr,"Error\n");
    return 1;
  }

  fclose(fp);

  return 0;
}
