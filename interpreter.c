#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "code.h"

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

    case C_ATTRIB_BOOL:
      printf("LET\n");
      getJump(depth+1);
      printf("%s\n", command->attr._attrib.var);
      printBool(command->attr._attrib_bool.expression, depth+1);
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

int temporaryRegistersUsed = 0;
char* newTempRegister() {
  char* temp = (char*) malloc(1024 * sizeof(char));
  sprintf(temp, "t%d", temporaryRegistersUsed++);
  return temp;
}

void printAtom(Atom *a) {

  switch (a->kind) {

    case A_VAR:
      printf("%s", a->data.var);
      break;

    case A_NUMBER:
      printf("%d", a->data.val);
      break;

  }

}

void printInstr (Instr *instruction) {

  switch (instruction->kind) {

    case I_ATTRIB:
      printAtom(instruction->instr.attrib.left);
      printf(" := ");
      printAtom(instruction->instr.attrib.right);
      printf(";\n");
      break;

    case I_BINOP:
      printAtom(instruction->instr.binop.result);
      printf(" := ");
      printAtom(instruction->instr.binop.first);
      printf(" ");
      switch (instruction->instr.binop.operator) {
        case 285:
          printf(" + ");
          break;
        case 286:
          printf(" - ");
          break;
        case 287:
          printf(" * ");
          break;
        case 288:
          printf(" / ");
          break;
        case 289:
          printf("%%");
          break;
      }
      printAtom(instruction->instr.binop.second);
      printf(";\n");
      break;
  }

}

void printListInstr (InstrList *list) {

  if (list != NULL) {
    printInstr(getFirst(list));
    printListInstr(nextInstrs(list));
  }

}

InstrList* compileExp(Expr* e, char *r) {
  char* r0 = (char*) malloc(1024* sizeof(char));
  char* r1 = (char*) malloc(1024* sizeof(char));
  switch (e->kind) {
    case E_INTEGER:
      r0 = r;
      return code_instruction_list(code_attribution(code_variable(r0), code_number(e->attr.value)), NULL);
    case E_VARIABLE:
      r0 = r;
      return code_instruction_list(code_attribution(code_variable(r0), code_variable(e->attr.var)), NULL);
    case E_OPERATION:
      r0 = strdup(newTempRegister());
      r1 = strdup(newTempRegister());
      InstrList* n0 = compileExp(e->attr.op.left, r0);
      InstrList* n1 = compileExp(e->attr.op.right, r1);
      return append(append(n0, n1), code_instruction_list(code_operation(e->attr.op.operator, code_variable(r), code_variable(r0), code_variable(r1)), NULL));
    default:
      printf("ERROR");
      return 0;
  }
}

InstrList* compileBool(BoolExpr* e, char *labelTrue, char *labelFalse) {

}

InstrList* compileCmd(Cmd* c) {

}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  }
  if (yyparse() == 0) {
      printListInstr(compileExp(ast_operation(285 , ast_variable("x"), ast_integer(4)), strdup("t0")));
      //printf("fn main()\n");
      //printCmdList(root, 1);
  }
  return 0;


}
