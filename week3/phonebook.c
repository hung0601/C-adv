#include <stdlib.h>
#include "phonebook.h"
#include <string.h>
PhoneBook createPhoneBook() {
  PhoneBook New;
  New.total=0;
  New.size=INITIAL_SIZE;
  New.entries=(PhoneEntry*)malloc(sizeof(PhoneEntry)*New.size);
  return New;
}

void dropPhoneBook(PhoneBook* book) {
  free(book->entries);
  return;
}

void addPhoneNumber(char * name, long number, PhoneBook* book) {
  if(book->total<book->size){
    (book->total)++;
    ((book->entries)+book->total-1)->number=number;
    strcpy(((book->entries)+book->total-1)->name,name);
  }
  else {
    book->size=book->size+INCREMENTAL_SIZE;
    book->entries=(PhoneEntry*)realloc(book->entries,sizeof(PhoneEntry)*book->size);
    addPhoneNumber(name,number,book);
}
  return;
}

PhoneEntry * getPhoneNumber(char * name, PhoneBook book){
  int i;
  if(book.entries!=NULL){
    for(i=0;i<book.total;i++){
      if(strcmp(((book.entries)+i)->name,name)==0) return book.entries+i;
    }
  }
  return NULL;
}
