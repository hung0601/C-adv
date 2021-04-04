#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__
#include "jrb.h"
typedef JRB Entry;
typedef struct {
  void (*freeKeyValue)(Jval,Jval);
  int (*compare)(Jval, Jval);
  JRB tree;
} SymbolTable;
void freeKeyValue(Jval k,Jval v);
int compare(Jval k1,Jval k2);
SymbolTable createSymbolTable(void (*freeKeyValue)(Jval,Jval),
                              int (*compare)(Jval, Jval));
void dropSymbolTable(SymbolTable* symtab);
void addEntry(Jval key, Jval value, SymbolTable* symtab);
Jval  getEntry(Jval key, SymbolTable tab);
#endif
