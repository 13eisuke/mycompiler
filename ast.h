#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;

#define MAXBUF 1024
#define SIMNAMELEN 64
#define MAXSIMENTRIES 100

typedef enum {
  PROGRAM_AST,
  DECLARATIONS_AST,
  DEFINE_AST,
  STATEMENTS_AST,
  ASSIGN_AST,
  ARRAY1_AST,
  ARRAY2_AST,
  NUM_AST,
  IDENT_AST,
  WHILE_AST,
  FOR_AST,
  IF_AST,
  ADD_AST,
  SUB_AST,
  MUL_AST,
  DIV_AST,
  REM_AST,
  EQ_AST,
  LT_AST,
  GT_AST,
  LTE_AST,
  GTE_AST
} NType;

typedef enum {
  TYPE_IDENT,
  TYPE_ARRAY1,
  TYPE_ARRAY2
} SType;

typedef enum {
  SCOPE_GLOBAL,
  SCOPE_LOCAL
}SScope;

typedef struct node {
  NType type;
  int ivalue;
  int ivalue2;
  char* variable;
  int number;
  struct node **child;
}Node;

typedef struct simTableEntry {
    char *name;
    SType type;
    SScope scope;
    int size;
    int value;
} SimTableEntry;

SimTableEntry simTable[MAXSIMENTRIES];
extern int sim_count;

Node* build_node1(NType t, Node* p1);
Node* build_node2(NType t, Node* p1, Node* p2);
Node* build_node3(NType t, Node* p1, Node* p2, Node* p3);
Node* build_node4(NType t, Node* p1, Node* p2, Node* p3, Node* p4);
Node* build_num_node(NType t, int n);
Node* build_ident_node(NType t, char *s);
void printNodes(Node *obj, int n);
Node* build_array1_node(NType t, char *s, int n);
Node* build_array2_node(NType t, char *s, int n, int m);
void print_code(Node *p);
int arithop(Node *p);
void condop(Node *p);
void codegen(Node* p);
