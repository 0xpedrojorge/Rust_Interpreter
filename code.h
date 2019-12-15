// CODE definitions
#ifndef _code_h_
#define _code_h_
#include "ast.h"

typedef struct _Atom Atom;           // Convenience typedef
typedef struct _Label Label;         // Convenience typedef
typedef struct _Instr Instr;         // Convenience typedef
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

// CODE for a label
struct _Label {
    char* lab_id;
};

// CODE for an instruction
struct _Instr {
  enum {
    I_ATTRIB,
    I_BINOP,
    I_GOTO_LAB,
    I_IF_THEN_ELSE,
    I_MK_LAB,
    I_PRINT,
    I_WRITE,
    I_READ
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
      char* label; // for the label id
    } goto_label;
    struct {
        int relOperator;  // EQ, NE, GT, LT, GE, LE
        Atom* left;       // first element of the comparison
        Atom* right;      // second element of the comparison
        char* labelTrue;  // label to go to in case comparison is True
        char* labelFalse; // label to go to in case comparison is False
    } if_then_else;
    struct {
      char* label; // for the label id
    } mk_label;
    struct {
      char* string; //String to be printed
      Atom* a;
    } _print;
    struct {
      char* string;
    } _write;
    struct {
      char* string
    } _read;
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
Label *code_label(char* s);
Instr *code_attribution(Atom *left, Atom *right);
Instr *code_operation(int operator, Atom *result, Atom *first, Atom *second);
Instr *code_goto_label(char* label);
Instr *code_if_then_else(int relop, Atom *left, Atom *right, char* labelTrue, char* labelFalse);
Instr *code_mk_label(char* label);
InstrList *code_instruction_list(Instr *first, InstrList *rest);

// Access functions (see implementation in code.c)
Instr *getFirst(InstrList *list);
InstrList  *nextInstrs(InstrList * list);
InstrList *append(InstrList *list1, InstrList *list2);

#endif