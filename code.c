#include <stdlib.h> // for malloc
#include <stdio.h> // for print
#include <string.h> // for strdup
#include "code.h" // CODE header
#include "ast.h"

Atom *code_number(int v) {
  Atom* node = (Atom*) malloc(sizeof(Atom));
  node->kind = A_NUMBER;
  node->data.val = v;
  return node;
}

Atom *code_variable(char* s) {
  Atom* node = (Atom*) malloc(sizeof(Atom));
  node->kind = A_VAR;
  node->data.var = s;
  return node;
}

Atom *code_nothing() {
  Atom* node = (Atom*) malloc(sizeof(Atom));
  node->kind = A_EMPTY;
  return node;
}

Label *code_label(char* s) {
    Label* node = (Label*) malloc(sizeof(Label));
    node->lab_id = s;
    return node;
}

Instr *code_attribution(Atom *left, Atom *right) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_ATTRIB;
  node->instr.attrib.left = left;
  node->instr.attrib.right = right;
  return node;
}

Instr *code_operation(int operator, Atom *result, Atom *first, Atom *second) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_BINOP;
  node->instr.binop.operator = operator;
  node->instr.binop.result = result;
  node->instr.binop.first = first;
  node->instr.binop.second = second;
  return node;
}

Instr *code_goto_label(char* label) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_GOTO_LAB;
  node->instr.goto_label.label = label;
  return node;
}

Instr *code_if_then_else(int relop, Atom *left, Atom *right, char* labelTrue, char* labelFalse) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_IF_THEN_ELSE;
  node->instr.if_then_else.relOperator = relop;
  node->instr.if_then_else.left = left;
  node->instr.if_then_else.right = right;
  node->instr.if_then_else.labelTrue = labelTrue;
  node->instr.if_then_else.labelFalse = labelFalse;
  return node;
}

Instr *code_mk_label(char* label) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = I_MK_LAB;
  node->instr.mk_label.label = label;
  return node;
}

InstrList *code_instruction_list(Instr *first, InstrList *rest) {
  InstrList* node = (InstrList*) malloc(sizeof(InstrList));
  node->firstInstr = first;
  node->restList = rest;
  return node;
}

Instr *getFirst(InstrList *list) {
  if (list == NULL) return NULL;
  return list->firstInstr;
}

InstrList  *nextInstrs(InstrList * list) {
  if (list == NULL) return NULL;
  return list->restList;
}

InstrList *append(InstrList *list1, InstrList *list2) {
  if (list2 == NULL) return list1;
  if (list1 == NULL) return list2;
  InstrList* node = (InstrList*) malloc(sizeof(InstrList));
  node = list1;
  while (list1->restList != NULL) {
    list1 = nextInstrs(list1);
  }
  list1->restList = list2;
  return  node;
}

