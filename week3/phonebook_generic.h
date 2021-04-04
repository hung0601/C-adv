#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__

typedef struct {
  void * key;
  void * value;
} Entry;
typedef struct {
  Entry * entries;
  int size, total;
  Entry (*makeNode)(void*, void*);
  int (*compare)(void*, void*);
} SymbolTable;
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5
Entry make_phonebook(void *key,void *value);
int Compare_name(void* key1,void*key2);
SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),
                              int (*compare)(void*, void*));
void dropSymbolTable(SymbolTable* tab);
Entry* getEntry(void* key, SymbolTable *tab);
void addEntry(void* key, void* value, SymbolTable* tab);
#endif
