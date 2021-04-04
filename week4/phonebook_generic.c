#include <stdio.h>
#include <stdlib.h>
#include "phonebook_generic.h"
#include "fields.h"
#include <string.h>

void freeKeyValue(Jval k,Jval v){
  char *key=jval_s(k);
  free(key);
}
int compare(Jval k1,Jval k2){
  return strcmp(jval_s(k1),jval_s(k2));
}
SymbolTable createSymbolTable(void (*freeKeyValue)(Jval,Jval),
                              int (*compare)(Jval,Jval)){
  SymbolTable symtab;
  symtab.freeKeyValue=freeKeyValue;
  symtab.compare=compare;
  symtab.tree= make_jrb();
  return symtab;
}
void dropSymbolTable(SymbolTable * symtab){
  JRB i;
  jrb_traverse(i,symtab->tree){
    symtab->freeKeyValue(i->key,i->val);
  }
  jrb_free_tree(symtab->tree);
}
void addEntry(Jval key, Jval value, SymbolTable* symtab){
  Jval k,v;
  JRB n= jrb_find_gen(symtab->tree,key,symtab->compare);
  if(n!=NULL){
    k=n->key;
    v=n->val;
    jrb_delete_node(n);
    symtab->freeKeyValue(k,v);
  }
  jrb_insert_gen(symtab->tree,key,value,symtab->compare);
}
Jval getEntry(Jval key , SymbolTable  symtab){
  JRB n=jrb_find_gen(symtab.tree,key,symtab.compare);
  if(n==NULL){
    return new_jval_v(NULL);
  }
  else return n->val;
}
