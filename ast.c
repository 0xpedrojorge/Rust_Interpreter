// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
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

BoolExpr* ast_boolean(int v) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(Expr));
  node->kind = B_BOOLEAN;
  node->attr.value = v;
  return node;
}

BoolExpr* ast_relation (int operator, Expr* left, Expr* right) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(Expr));
  node->kind = B_EXPRESSION;
  node->attr.relop.operator = operator;
  node->attr.relop.left = left;
  node->attr.relop.right = right;
  return node;
}
