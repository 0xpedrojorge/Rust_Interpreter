// CODE definitions
#ifndef _code_h_
#define _code_h_
#include "ast.h"

typedef struct _Atom Atom; //Convenience typedef
typedef struct _Instr Instr; // Convenience typedef
typedef struct _InstrList InstrList; // Convenience typedef

// CODE for an atom
struct _Atom {
  enum {
    A_NUMBER,
    A_VAR,
    A_EMPTY
  } kind;
  union {
    int val;   // if the atom is a value
    char* var; // if the atom is a variable
  } data;
};

// CODE for an instruction
struct _Instr {
  enum {
    I_ATTRIB,
    I_BINOP
  } kind;
  union {
    struct {
      Atom *left;  // for the left side of the attribution
      Atom *right; // for the right side of the attribution
    } attrib;
    struct {
      int operator; // PLUS, MINUS, DIV, MULT
      Atom *result; // for the result
      Atom *first;  // for the first element of the operation
      Atom *second; // for the second element of the operation
    } binop;
    struct {
      int operator; // EQ, NE, LT, GT, LE, GE
      Atom *first;
      Atom *second;
      char *labelTrue;
      char *labelFalse;
    } relop;
  } instr;
};

// CODE for an instruction list
struct _InstrList {
  Instr *firstInstr;
  InstrList *restList;
};

// Constructor functions (see implementation in code.c)
Atom *code_number(int v);
Atom *code_variable(char* s);
Atom *code_nothing();
Instr *code_attribution(Atom *left, Atom *right);
Instr *code_operation(int operator, Atom *result, Atom *first, Atom *second);
InstrList *code_instruction_list(Instr *first, InstrList *rest);

// Access functions (see implementation in code.c)
Instr *getFirst(InstrList *list);
InstrList  *nextInstrs(InstrList * list);
InstrList *append(InstrList *list1, InstrList *list2);

void printAtom(Atom *a);
void printInstr (Instr *instruction);
void printListInstr (InstrList *list);
InstrList* compileExp(Expr* e, char *r);

#endif