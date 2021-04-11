#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__
#include "btree.h"
BTA * createPhoneBook(char * name);
void addPhoneNumber(BTA * btr,char * name, BTint number);
BTint getPhoneNumber(BTA *btr,char * name);
void PrintPhoneBook(BTA *btr);
#endif
