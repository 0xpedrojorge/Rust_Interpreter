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

InstrList* compileCmdList(CmdList* list);

int temporaryRegistersUsed = 0;
char* newTempRegister() {
  if (temporaryRegistersUsed == 8)
    temporaryRegistersUsed = 0;
  char* temp = (char*) malloc(1024 * sizeof(char));
  sprintf(temp, "t%d", temporaryRegistersUsed++);
  return temp;
}
int labelsUsed = 0;
char* newLabel() {
    char* label = (char*) malloc(1024 * sizeof(char));
    sprintf(label, "l%d", labelsUsed++);
    return label;
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

void printLabel(Label *l) {
  printf("%s", l->lab_id);
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

    case I_GOTO_LAB:
      printf("GOTO ");
      printf("%s", instruction->instr.goto_label.label);
      printf(";\n");
      break;

    case I_IF_THEN_ELSE:
      printf("IF ");
      printAtom(instruction->instr.if_then_else.left);
      switch (instruction->instr.if_then_else.relOperator) {
        case 279:
          printf(" == ");
          break;
        case 280:
          printf(" != ");
          break;
        case 281:
          printf(" < ");
          break;
        case 282:
          printf(" > ");
          break;
        case 283:
          printf(" <= ");
          break;
        case 284:
          printf(" >= ");
          break;
      }
      printAtom(instruction->instr.if_then_else.right);
      printf(" THEN ");
      printf("%s", instruction->instr.if_then_else.labelTrue);
      printf(" ELSE ");
      printf("%s", instruction->instr.if_then_else.labelFalse);
      printf(";\n");
      break;

    case I_MK_LAB:
      printf("LAB ");
      printf("%s", instruction->instr.mk_label.label);
      printf(";\n");
      break;

    default:
      printf("ERROR\n");
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
  char* r0 = (char*) malloc(1024* sizeof(char));
  char* r1 = (char*) malloc(1024* sizeof(char));

  switch (e->kind) {
    case B_BOOLEAN:
      r0 = strdup(newTempRegister());
      return code_instruction_list(code_attribution(code_variable(r0), code_variable(e->attr.value)), NULL);
    case B_EXPRESSION:
      r0 = strdup(newTempRegister());
      r1 = strdup(newTempRegister());
      InstrList* n0 = compileExp(e->attr.relop.left, r0);
      InstrList* n1 = compileExp(e->attr.relop.right, r1);
      return append(append(n0, n1), code_instruction_list(code_if_then_else(e->attr.relop.operator, code_variable(r0), code_variable(r1), labelTrue, labelFalse), NULL));
    default:
      printf("ERROR");
      return 0;
  }
}

InstrList* compileCmd(Cmd* c) {
    char* l0 = (char*) malloc(1024* sizeof(char));
    char* l1 = (char*) malloc(1024* sizeof(char));
    char* l2 = (char*) malloc(1024* sizeof(char));

    switch (c->kind) {
      case C_ATTRIB:
        return compileExp(c->attr._attrib.expression, c->attr._attrib.var);

      case C_IF:
          l0 = strdup(newLabel());
          l1 = strdup(newLabel());
          InstrList* n0 = compileBool(c->attr._if.condition, l0, l1);
          n0 = append(n0, code_instruction_list(code_mk_label(l0), compileCmdList(c->attr._if.execution)));
          return append(n0, code_instruction_list(code_mk_label(l1), NULL));

        case C_IF_ELSE:
          l0 = strdup(newLabel());
          l1 = strdup(newLabel());
          l2 = strdup(newLabel());
          InstrList* n1 = compileBool(c->attr._if_else.condition, l0, l1);
          n1 = append(n1, code_instruction_list(code_mk_label(l0), compileCmdList(c->attr._if_else.firstCase)));
          n1 = append(n1, code_instruction_list(code_goto_label(l2), code_instruction_list(code_mk_label(l1), compileCmdList(c->attr._if_else.secondCase))));
          return append (n1, code_instruction_list(code_mk_label(l2), NULL));

        case C_WHILE:
          l0 = strdup(newLabel());
          l1 = strdup(newLabel());
          l2 = strdup(newLabel());
          InstrList* n2 = code_instruction_list(code_mk_label(l0), compileBool(c->attr._while.condition, l1, l2));
          n2 = append(n2, code_instruction_list(code_mk_label(l1), compileCmdList(c->attr._while.execution)));
          return append(n2, code_instruction_list(code_goto_label(l0), code_instruction_list(code_mk_label(l2), NULL)));

        case C_PRINT:
        case C_WRITE:
        case C_READ:
        default:
          printf("ERROR");
          return 0;
    }
}

InstrList* compileCmdList(CmdList* list) {
  if (list == NULL)
    return NULL;

  if (list->restList == NULL)
      return compileCmd(list->firstCommand);

  return append(compileCmd(list->firstCommand), compileCmdList(list->restList));
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
      //printListInstr(compileExp(ast_operation(285, ast_variable("x"), ast_integer(2)), strdup("t0")));
      //printf("fn main()\n");
      printListInstr(compileCmdList(root));
      //printCmdList(root, 1);
  }
  return 0;


}
