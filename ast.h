
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc 
      struct _Expr *left;
      struct _Expr *right;
    } op; // for binary expressions
  } attr;
};

// AST for boolean expressions
struct _BoolExpr {
  enum {
    B_BOOLEAN,
    B_EXPRESSION
  } kind;
  union {
    int value; // for true or false
    struct {
      int operator; // EQ, NE, GT, LT, GE, LE
      struct _Expr *left;
      struct _Expr *right;
    } relop; // for relational operations
  } attr;
};

// AST for commands
/*
struct _Cmd {
  enum {
    C_ATTRIB,
    C_IF,
    C_IF_ELSE,
    C_WHILE,
    C_PRINT,
    C_READ
  } kind;
  union {
    struct {
      int operator; // ATTRIB
      struct _Expr *attribution;
    } attrib;
    struct {
      int operator; // IF
      struct _BoolExpr *
    } _if;
  } attr;
};
 */

typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr Boolexpr; // Convenience typedef
typedef struct _Cmd Cmd; // Convenience typedef

// Constructor functions (see implementation in ast.c)
Expr *ast_integer(int v);
Expr *ast_operation(int operator, Expr *left, Expr *right);
Boolexpr *ast_boolean(int v);
Boolexpr *ast_relation(int operator, Expr *left, Expr *right);

#endif
