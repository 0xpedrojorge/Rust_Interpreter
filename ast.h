
// AST definitions
#ifndef __ast_h__
#define __ast_h__

typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr; // Convenience typedef
typedef struct _Cmd Cmd; // Convenience typedef
typedef struct _CmdList CmdList; // Convenience typedef

// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION,
    E_VARIABLE
  } kind;
  union {
    int value; // for integer values
    char* var; // for variables
    struct {
      int operator; // PLUS, MINUS, etc 
      Expr *left;
      Expr *right;
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
    char* value; // for true or false
    struct {
      int operator; // EQ, NE, GT, LT, GE, LE
      Expr *left;
      Expr *right;
    } relop; // for relational operations
  } attr;
};

// AST for commands

struct _Cmd {
  enum {
    C_ATTRIB,
    C_ATTRIB_BOOL,
    C_IF,
    C_IF_ELSE,
    C_WHILE,
    C_PRINT,
    C_WRITE,
    C_READ
  } kind;
  union {
    struct {
      char* var; // variable
      Expr *expression; // expression
    } _attrib;
    struct {
      char* var; // variable
      BoolExpr *expression; // expression
    } _attrib_bool;
    struct {
      BoolExpr *condition;
      CmdList *execution; // in case condition is true
    } _if;
    struct {
      BoolExpr *condition;
      CmdList *firstCase; // in case condition is true
      CmdList *secondCase; // in case condition is false
    } _if_else;
    struct {
      BoolExpr *condition;
      CmdList *execution; // in case condition is true
    } _while;
    struct {
      char* string;
      char* var;
    } _print;
    struct {
      char* string;
    }_write;
    struct {
      char* string;
    }_read;
  } attr;
};

struct _CmdList {
  Cmd *firstCommand;
  CmdList *restList;
};

// Constructor functions (see implementation in ast.c)
Expr *ast_integer(int v);
Expr *ast_variable(char* s);
Expr *ast_operation(int operator, Expr *left, Expr *right);
BoolExpr *ast_boolean(char* v);
BoolExpr *ast_relation(int operator, Expr *left, Expr *right);
Cmd *ast_attribution(char* v, Expr *e);
Cmd *ast_attribution_bool(char* v, BoolExpr *e);
Cmd *ast_if_condition(BoolExpr *cond, CmdList *exec);
Cmd *ast_if_else_condition(BoolExpr *cond, CmdList *exec1, CmdList *exec2);
Cmd *ast_while_loop(BoolExpr *cond, CmdList *exec);
Cmd *ast_print(char* string, char* var);
Cmd *ast_write(char* string);
Cmd *ast_read(char* string);
CmdList * ast_command_list(Cmd *first, CmdList *rest);

#endif
