#include "ast.h"
#include "compiler.tab.h"

int label_count = 0;
int stack_pointer  = 0;
int sim_count;

int arithop(Node *p){
  int a = 0, b = 0;
  switch(p->type){
  case ADD_AST:
    if(p->child[0]->type == NUM_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == NUM_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == IDENT_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      a = arithop(p->child[0]);
      stack_pointer = stack_pointer - 4;
      b = arithop(p->child[1]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
      stack_pointer = stack_pointer + 4;
    }
    fprintf(fp,"\tadd\t$v0, $t0, $t1\n");
    fprintf(fp,"\tsw\t$v0, %d($sp)\n",stack_pointer);
    return stack_pointer;
    break;

  case SUB_AST:
    if(p->child[0]->type == NUM_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == NUM_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == IDENT_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      a = arithop(p->child[0]);
      stack_pointer = stack_pointer - 4;
      b = arithop(p->child[1]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
      stack_pointer = stack_pointer + 4;
    }
    fprintf(fp,"\tsub\t$v0, $t0, $t1\n");
    fprintf(fp,"\tsw\t$v0, %d($sp)\n",stack_pointer);
    return stack_pointer;
    break;

  case MUL_AST:
    if(p->child[0]->type == NUM_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == NUM_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == IDENT_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      a = arithop(p->child[0]);
      stack_pointer = stack_pointer - 4;
      b = arithop(p->child[1]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
      stack_pointer = stack_pointer + 4;
    }
    fprintf(fp,"\tmult\t$t0, $t1\n");
    fprintf(fp, "\tmflo\t$v0\n");
    fprintf(fp,"\tsw\t$v0, %d($sp)\n",stack_pointer);
    return stack_pointer;
    break;

  case DIV_AST:
    if(p->child[0]->type == NUM_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == NUM_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == IDENT_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      a = arithop(p->child[0]);
      stack_pointer = stack_pointer - 4;
      b = arithop(p->child[1]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
      stack_pointer = stack_pointer + 4;
    }
    fprintf(fp,"\tdiv\t$t0, $t1\n");
    fprintf(fp, "\tmflo\t$v0\n");
    fprintf(fp,"\tsw\t$v0, %d($sp)\n",stack_pointer);
    return stack_pointer;
    break;

  case REM_AST:
    if(p->child[0]->type == NUM_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == NUM_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == NUM_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type == IDENT_AST){
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type == IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      b = arithop(p->child[1]);
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
      fprintf(fp,"\tlw\t$t0, 0($t2)\n");
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == NUM_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type == IDENT_AST){
      a = arithop(p->child[0]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
      fprintf(fp,"\tlw\t$t1, 0($t2)\n");
      fprintf(fp, "\tnop\n");
    }
    else if(p->child[0]->type != NUM_AST && p->child[0]->type != IDENT_AST && p->child[1]->type != NUM_AST && p->child[1]->type != IDENT_AST){
      a = arithop(p->child[0]);
      stack_pointer = stack_pointer - 4;
      b = arithop(p->child[1]);
      fprintf(fp,"\tlw\t$t0, %d($sp)\n",a);
      fprintf(fp, "\tnop\n");
      fprintf(fp,"\tlw\t$t1, %d($sp)\n",b);
      fprintf(fp, "\tnop\n");
      stack_pointer = stack_pointer + 4;
    }
    fprintf(fp,"\tdiv\t$t0, $t1\n");
    fprintf(fp, "\tmfhi\t$v0\n");
    fprintf(fp,"\tsw\t$v0, %d($sp)\n",stack_pointer);
    return stack_pointer;
    break;
  }
}

void condop(Node* p){
  if(p->child[0]->type == NUM_AST){
    fprintf(fp,"\tli\t$t0, %d\n",p->child[0]->ivalue);
  }
  else if(p->child[0]->type == IDENT_AST){
    fprintf(fp,"\tla\t$t2, _%s\n",p->child[0]->variable);
    fprintf(fp,"\tlw\t$t0, 0($t2)\n");
    fprintf(fp, "\tnop\n");
  }
  else {
    codegen(p->child[0]);
    fprintf(fp,"\tli\t$t0, $v0\n");
  }
  if(p->child[1]->type == NUM_AST){
    fprintf(fp,"\tli\t$t1, %d\n",p->child[1]->ivalue);
  }
  else if(p->child[1]->type == IDENT_AST){
    fprintf(fp,"\tla\t$t2, _%s\n",p->child[1]->variable);
    fprintf(fp,"\tlw\t$t1, 0($t2)\n");
    fprintf(fp, "\tnop\n");
  }
  else {
    codegen(p->child[1]);
    fprintf(fp,"\tli\t$t1, $v0\n");
  }

  switch(p->type){
  case EQ_AST:
    break;
  case LT_AST:
    fprintf(fp, "\tslt\t$v0, $t0, $t1\n");
    break;
  case GT_AST:
    fprintf(fp, "\tslt\t$v0, $t1, $t0\n");
    break;
  case LTE_AST:
    break;
  case GTE_AST:
    break;
  }

}

void codegen(Node* p){
  int label;
  int i;

  switch(p->type){
  case PROGRAM_AST:
  case DECLARATIONS_AST:
  case STATEMENTS_AST:
  case IDENT_AST:    
  case ARRAY1_AST:
    for (i = 0; i < p->number; i++) {
      if (p->child[i] != NULL) {
	codegen(p->child[i]);
      }
    }
    break;
  case NUM_AST:
    fprintf(fp, "\tli\t$v0, %d\n", p->ivalue);
    break;
  case WHILE_AST:
    label = label_count;
    fprintf(fp,"L%d:\n",label);
    label_count++;
    if(p->child[0]!=NULL){
      codegen(p->child[0]);
    }
    fprintf(fp,"\tbeq\t$v0, $zero, L%d\n",label_count);
    fprintf(fp,"\tnop\n");

    if(p->child[1]!=NULL){
      codegen(p->child[1]);
    }
    fprintf(fp, "\tj\tL%d\n", label);
    fprintf(fp,"\tnop\n");
    fprintf(fp,"L%d:\n",label_count);
    break;


  case ADD_AST:
  case SUB_AST:
  case MUL_AST:
  case DIV_AST:
  case REM_AST:
    arithop(p);
    break;
  case EQ_AST:
  case LT_AST:
  case GT_AST:
  case LTE_AST:
  case GTE_AST:
    condop(p);
    break;

  case DEFINE_AST:
    simTable[sim_count].name = (char*)malloc(SIMNAMELEN);
    simTable[sim_count].name = p->variable;
    sim_count++;
    break;

  case ASSIGN_AST:
    codegen(p->child[1]);
    for (i = 0; i < sim_count; i++){
      if (strcmp(simTable[i].name,p->child[0]->variable) == 0){
	break;
      }
    }
    fprintf(fp,"\tla\t$t2, _%s\n", simTable[i].name);
    fprintf(fp,"\tsw\t$v0, 0($t2)\n");     
    break;
  } 
}

Node* build_node1(NType t, Node* p1) {
  Node *p;
  if ((p = (Node *)malloc(sizeof(Node))) == NULL) {
    //yyerror("out of memory");
  }
  p->type = t;
  p->number = 1;
 
  p->child = malloc(sizeof(Node *) * p->number);
  p->child[0] = p1;

  return p;
}

Node* build_node2(NType t, Node* p1, Node* p2) {
  Node *p;
  if ((p = (Node *)malloc(sizeof(Node))) == NULL) {
    //yyerror("out of memory");
  }
  p->type = t;
  p->number = 2;
 
  p->child = malloc(sizeof(Node *) * p->number);
  p->child[0] = p1;
  p->child[1] = p2;

  return p;
}

Node* build_node3(NType t, Node* p1, Node* p2, Node* p3) {
  Node *p;

  if ((p = (Node *)malloc(sizeof(Node))) == NULL) {
    //yyerror("out of memory");
  }
  p->type = t;
  p->number = 3;
   
  p->child = malloc(sizeof(Node *) * p->number);
  p->child[0] = p1;
  p->child[1] = p2;
  p->child[2] = p3;

  return p;
}

Node* build_node4(NType t, Node* p1, Node* p2, Node* p3, Node* p4) {
  Node *p;

  if ((p = (Node *)malloc(sizeof(Node))) == NULL) {
    //yyerror("out of memory");
  }
  p->type = t;
  p->number = 4;
   
  p->child = malloc(sizeof(Node *) * p->number);
  p->child[0] = p1;
  p->child[1] = p2;
  p->child[2] = p3;
  p->child[3] = p4;
}

Node* build_num_node(NType t, int n) {
  Node *p;
  if ((p = (Node *)malloc(sizeof(Node))) == NULL){
    // yyerror("out of memory");
  }

  p->type = t;
  p->ivalue = n;

  return p;
}

Node* build_ident_node(NType t, char *s) {
  Node *p;
  if ((p = (Node *)malloc(sizeof(Node))) == NULL){
    //yyerror("out of memory");
  }
  p->type = t;
  if ((p->variable = (char *)malloc(sizeof(MAXBUF))) == NULL){
    //yyerror("out of memory");
  }

  strncpy(p->variable, s, MAXBUF);

  return p;
}

Node* build_array1_node(NType t, char *s, int n){
  Node *p;
  if(( p = (Node *)malloc(sizeof(Node))) == NULL){
    yyerror("out of memory");
  }
  p->type = t;
  if ((p->variable = (char *)malloc(sizeof(MAXBUF))) == NULL){
    yyerror("out of memory");
  }

  strncpy(p->variable, s, MAXBUF);
  p->ivalue = n;
  
  return p;
}

Node* build_array2_node(NType t, char *s, int n, int m){
  Node *p;
  if(( p = (Node *)malloc(sizeof(Node))) == NULL){
    yyerror("out of memory");
  }
  p->type = t;
  if((p->variable = (char *)malloc(sizeof(MAXBUF))) == NULL){
    yyerror("out of memory");
  }
  strncpy(p->variable, s, MAXBUF);
  p->ivalue = n;
  p->ivalue2 = m;
  return p;
}

void printNodes(Node *obj, int n){
  int i = 0;
  
  i = n;
  while(i > 0){
    printf("\t");
    i--;
  }

  if (obj != NULL) {
    switch(obj->type){
    case 0:
      printf("PROGRAM_AST\t");
      break;
    case 1:
      printf("DECLARATIONS_AST\t");
      break;
    case 2:
      printf("DEFINE_AST\t");
      break;
    case 3:
      printf("STATEMENTS_AST\t");
      break;
    case 4:
      printf("ASSIGN_AST\t");
      break;
    case 5:
      printf("ARRAY1_AST\t");
      break;
    case 6:
      printf("ARRAY2_AST\t");
      break;
    case 7:
      printf("NUM_AST %d\t", obj->ivalue);
      break;
    case 8:
      printf("IDENT_AST %s\t", obj->variable);
      break;
    case 9:
      printf("WHILE_AST \t");
      break;
    case 10:
      printf("FOR_AST \t");
      break;
    case 11:
      printf("IF_STMT \t");
      break;
    case 12:
      printf("ADD_AST \t");
      break;
    case 13:
      printf("SUB_AST \t");
      break;
    case 14:
      printf("MUL_AST \t");
      break;
    case 15:
      printf("DIV_AST \t");
      break;
    case 16:
      printf("REM_AST \t");
      break;
    case 17:
      printf("EQ_AST\t");
      break;
    case 18:
      printf("LT_AST\t");
      break;
    case 19:
      printf("GT_AST\t");
      break;
    case 20:
      printf("LTE_AST\t");
      break;
    case 21:
      printf("GTE_AST\t");
      break;
    default:
      break;
    }
    
   printf("\n");

   n++;
   for (i = 0; i < obj->number; i++) {
     if (obj->child[i] != NULL) {
       printNodes(obj->child[i],n);
     }
   }
  }
}

