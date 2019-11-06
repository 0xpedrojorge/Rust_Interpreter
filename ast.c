// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_variable(char* s) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VARIABLE;
  node->attr.var = s;
  return node;
}

Expr* ast_operation (int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

BoolExpr* ast_boolean(char* v) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = B_BOOLEAN;
  node->attr.value = v;
  return node;
}

BoolExpr* ast_relation (int operator, Expr* left, Expr* right) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = B_EXPRESSION;
  node->attr.relop.operator = operator;
  node->attr.relop.left = left;
  node->attr.relop.right = right;
  return node;
}

Cmd* ast_attribution(char* v, Expr* e) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_ATTRIB;
  node->attr._attrib.var = v;
  node->attr._attrib.expression = e;
  return node;
}

Cmd* ast_if_condition(BoolExpr* cond, CmdList* exec) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_IF;
  node->attr._if.condition = cond;
  node->attr._if.execution = exec;
  return node;
}

Cmd* ast_if_else_condition(BoolExpr* cond, CmdList* exec1, CmdList* exec2) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_IF_ELSE;
  node->attr._if_else.condition = cond;
  node->attr._if_else.firstCase = exec1;
  node->attr._if_else.secondCase = exec2;
  return node;
}

Cmd* ast_while_loop(BoolExpr* cond, CmdList* exec) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_WHILE;
  node->attr._while.condition = cond;
  node->attr._while.execution = exec;
  return node;
}

Cmd *ast_print(char* string, char* var) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_PRINT;
  node->attr._print.string = string;
  node->attr._print.var = var;
  return node;
}

Cmd *ast_write(char* string) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_WRITE;
  node->attr._write.string = string;
  return node;
}

Cmd *ast_read(char* string) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_READ;
  node->attr._read.string = string;
  return node;
}

CmdList* ast_command_list(Cmd* first, CmdList* rest) {
  CmdList* node = (CmdList*) malloc(sizeof(CmdList));
  node->firstCommand = first;
  node->restList = rest;
  return node;
}