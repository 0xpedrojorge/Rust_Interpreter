// Tokens
%token
  INT
  VAR
  TRUE
  FALSE
  _LET
  _IF
  _ELSE
  _WHILE
  _ATTRIB
  AT
  SC
  OCB
  CCB
  OP
  CP
  _PRINT
  _READ
  string


// Operator associativity & precedence
%precedence EQ NE LT GT LE GE
%left PLUS MINUS
%left MULT DIV MOD


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  char* stringValue;
  Expr* exprValue;
  BoolExpr* boolExprValue;
  Cmd* cmdValue;
  CmdList* cmdListValue;
}

%type <intValue> INT
%type <stringValue> VAR
%type <intValue> TRUE
%type <intValue> FALSE
%type <stringValue> string
%type <exprValue> expr
%type <boolExprValue> boolexpr
%type <cmdValue> cmd
%type <cmdListValue> cmdlist

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>ma
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
CmdList* root;
}

%%
program: cmdlist { root = $1; }

expr:
  INT {
    $$ = ast_integer($1);
  }
  |
  VAR {
    $$ = ast_variable($1);
  };
  |
  expr PLUS expr {
    $$ = ast_operation(PLUS, $1, $3);
  }
  |
  expr MINUS expr {
    $$ = ast_operation(MINUS, $1, $3);
  }
  |
  expr MULT expr {
    $$ = ast_operation(MULT, $1, $3);
  }
  |
  expr DIV expr {
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr MOD expr {
    $$ = ast_operation(MOD, $1, $3);
  }
  ;

boolexpr:
  TRUE {
    $$ = ast_boolean(1);
  }
  |
  FALSE {
    $$ = ast_boolean(0);
  }
  |
  expr EQ expr {
    $$ = ast_relation(EQ, $1, $3);
  }
  |
  expr NE expr {
    $$ = ast_relation(NE, $1, $3);
  }
  |
  expr LT expr {
    $$ = ast_relation(LT, $1, $3);
  }
  |
  expr GT expr {
    $$ = ast_relation(GT, $1, $3);
  }
  |
  expr LE expr {
    $$ = ast_relation(LE, $1, $3);
  }
  |
  expr GE expr {
    $$ = ast_relation(GE, $1, $3);
  }
  ;

cmd:
  _LET VAR AT expr {
    $$ = ast_attribution($2, $4);
  }
  |
  _IF boolexpr OCB expr CCB _ELSE OCB expr CCB {
    $$ = ast_if_else_condition($2, $4, $8);
  }
  |
  _IF boolexpr OCB expr CCB {
    $$ = ast_if_condition($2, $4);
  }
  |
  _WHILE boolexpr OCB expr CCB {
    $$ = ast_while_loop($2, $4);
  }
  |
  _PRINT OP string CP {
    $$ = ast_write($3);
  }
  |
  VAR AT _READ {
    $$ = ast_read($1);
  }
  ;

cmdlist:
  cmd cmdlist {
    $$ = ast_command_list($1, $2);
  }

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

