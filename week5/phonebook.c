#include <stdio.h>
#include <stdlib.h>
#include "phonebook.h"
#include <string.h>
BTA * createPhoneBook(char * name) {
  return btcrt(name,0,FALSE);
}

void addPhoneNumber(BTA * btr,char * name, BTint number) {
  BTint val;
  if(bfndky(btr,name,&val)==0) bupdky(btr,name,number);
  else binsky(btr,name,number);
  return;
}

BTint getPhoneNumber(BTA *btr,char * name){
  BTint val;
  if (bfndky(btr,name,&val)==0) return val;
  else return -1;
}
void PrintPhoneBook(BTA *btr){
  char name[ZKYLEN];
  BTint val;
  btpos(btr,ZSTART);
  while (bnxtky(btr,name,&val) == 0){
    printf("%-40s%-15d\n",name,val);
  }
  return;
}
