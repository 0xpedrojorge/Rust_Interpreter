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

