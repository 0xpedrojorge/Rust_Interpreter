#include <stdio.h>
#include "parser.h"

void printCmdList(CmdList* list, int depth);
void getJump(int depth) {
  for(int i=0; i<depth; i++) {
    printf("| ");
  }

}

void printExpr(Expr* exp, int depth) {

  getJump(depth);

  switch (exp->kind) {

    case E_INTEGER:
      printf("%d\n", exp->attr.value);
      break;

    case E_VARIABLE:
      printf("%s\n", exp->attr.var);
      break;

    case E_OPERATION:
      switch (exp->attr.op.operator) {
        case 285:
          printf("+\n");
          break;
        case 286:
          printf("-\n");
          break;
        case 287:
          printf("*\n");
          break;
        case 288:
          printf("/\n");
          break;
        case 289:
          printf("%%\n");
          break;
      }
      printExpr(exp->attr.op.left, depth+1);
      printExpr(exp->attr.op.right, depth+1);
      break;

  }

}

void printBool(BoolExpr* b, int depth) {

  getJump(depth);

  switch (b->kind) {

    case B_BOOLEAN:
      printf("%s\n", b->attr.value);
      break;

    case B_EXPRESSION:
      switch (b->attr.relop.operator) {
        case 279:
          printf("==\n");
          break;
        case 280:
          printf("!=\n");
          break;
        case 281:
          printf("<\n");
          break;
        case 282:
          printf(">\n");
          break;
        case 283:
          printf("<=\n");
          break;
        case 284:
          printf(">=\n");
          break;
      }
      printExpr(b->attr.relop.left, depth+1);
      printExpr(b->attr.relop.right, depth+1);
      break;

  }

}

void printCmd(Cmd* command, int depth) {

  getJump(depth);

  switch (command->kind) {

    case C_ATTRIB:
      printf("LET\n");
      getJump(depth+1);
      printf("%s\n", command->attr._attrib.var);
      printExpr(command->attr._attrib.expression, depth+1);
      break;

    case C_IF:
      printf("IF\n");
      printBool(command->attr._if.condition, depth+1);
      printCmdList(command->attr._if.execution, depth+1);
      break;

    case C_IF_ELSE:
      printf("IF\n");
      printBool(command->attr._if_else.condition, depth+1);
      printCmdList(command->attr._if_else.firstCase, depth +1);
      getJump(depth);
      printf("ELSE\n");
      printCmdList(command->attr._if_else.secondCase, depth +1);
      break;

    case C_WHILE:
      printf("WHILE\n");
      printBool(command->attr._while.condition, depth+1);
      printCmdList(command->attr._while.execution, depth+1);
      break;

    case C_PRINT:
      printf("println!()\n");
      getJump(depth+1);
      printf("%s\n", command->attr._print.string);
      getJump(depth+1);
      printf("%s\n", command->attr._print.var);
      break;

    case C_WRITE:
      printf("println!()\n");
      getJump(depth+1);
      printf("%s\n", command->attr._write.string);
      break;

    case C_READ:
      printf("read_line()\n");
      getJump(depth+1);
      printf("%s\n", command->attr._read.string);
      break;

  }
}

void printCmdList(CmdList* list, int depth) {

  if (list != NULL) {
    printCmd(list->firstCommand, depth);
    printCmdList(list->restList, depth);
  }

}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
      printf("fn main()\n");
      printCmdList(root, 1);
  }
  return 0;


}
