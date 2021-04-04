#include <stdlib.h>
#include "phonebook_generic.h"
#include <string.h>
Entry make_phonebook(void *key,void *value){
  Entry New;
  New.key = strdup( (char*)key);
  New.value = malloc(sizeof(long));
  memcpy( New.value, value, sizeof(long) );
  return New;
}
int Compare_name(void* key1,void*key2){
  return strcmp((char*)key1,(char*)key2);
}
SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),
                          int (*compare)(void*, void*)) {
  SymbolTable New;
  New.makeNode=makeNode;
  New.compare=compare;
  New.total=0;
  New.size=INITIAL_SIZE;
  New.entries=(Entry*)malloc(sizeof(Entry)*INITIAL_SIZE);
  return New;
}
void dropSymbolTable(SymbolTable *tab) {
  free(tab->entries);
  tab->makeNode=NULL;
  tab->compare=NULL;
  return;
}
Entry* getEntry(void *key, SymbolTable *tab){
  int i;
  if(tab!=NULL && tab->entries!=NULL){
    for(i=0;i<tab->total;i++){
      if(tab->compare(key,tab->entries[i].key)==0) return tab->entries+i;
    }
  }
  return NULL;
}
void addEntry(void* key,void *value,SymbolTable* tab) {
  if(tab->total>=tab->size){
    tab->size+=INCREMENTAL_SIZE;
    tab->entries=(Entry*)realloc(tab->entries,sizeof(Entry)*tab->size);
  }
  if(getEntry(key,tab)==NULL) tab->entries[(tab->total)++]=tab->makeNode(key,value);
  else{
    *(getEntry(key,tab))=tab->makeNode(key,value);
  }
  return;
}
