%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return MOD; }
"true" { return TRUE; }
"false" { return FALSE; }
"==" { return EQ; }
"!=" { return NE; }
"<" { return LT; }
">" { return GT; }
"<=" { return LE; }
">=" { return GE; }
"let" { return _LET; }
"if" { return _IF; }
"else" { return _ELSE; }
"while" { return _WHILE; }
"=" { return AT; }
";" { return SC; }
"{" { return OCB; }
"}" { return CCB; }
"(" { return OP; }
")" { return CP; }
"," { return C; }
"&" { return ANDCOM; }
"println!" { return _PRINT; }
"read_line" { return _READ; }
"fn main()" { return START; }
[a-z][a-zA-Z0-9]* {
    yylval.charValue = strdup(yytext);
    return VAR;
}
\".*\" {
  yylval.charValue = strdup(yytext);
  return STRING;
}
.  { yyerror("unexpected character"); }
%%

