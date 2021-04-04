#include <stdio.h>
#include "phonebook_generic.h"

int main() {
  SymbolTable pb = createSymbolTable(make_phonebook,Compare_name);
  Entry *e;
  char name[80];
  long number;
  number=1545454;
  addEntry("Duc", &number, &pb);
  number=4545455;
  addEntry("Minh", &number, &pb);
  number=4233222;
  addEntry("Huong", &number, &pb);
  printf("Nhap ten:");
  gets(name);
  if ((e = getEntry(name,&pb)) != NULL)
    printf("Phone number of %s is:%ld\n",name, *(long*)e->value);
  else
    printf("Can\'t find phone number of %s\n",name);
  dropSymbolTable(&pb);
  return 0;  
}
