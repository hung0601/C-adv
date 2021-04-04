#include <stdio.h>
#include "fields.h"
#include "jval.h"
#include "jrb.h"
#include <string.h>
#include "phonebook_generic.h"
int main() {
  char s[80];
  int c;
  JRB i;
  SymbolTable tab;
  Jval key,value,ptr;
  tab=createSymbolTable(freeKeyValue,compare);
  do{
  printf("----------------------------------------------\n");
  printf("Chuong trinh phonebook\n");
  printf(" 1.In phonebook\n");
  printf(" 2.Them phone node\n");
  printf(" 3.Tim Phonenode\n");
  printf(" 0.Thoat\n");
  printf("Nhap lua chon:");
  scanf("%d%*c",&c);
  printf("----------------------------------------------\n");
  switch(c){
  case 1:
    jrb_traverse(i,tab.tree) {
      printf("%-20s%-10ld\n", i->key.s,i->val.l);
    }
    break;
  case 2:
    strdup(s);
    printf("Nhap Ten:");
    gets(s);
    key=new_jval_s(strdup(s));
    printf("Nhap sdt:");
    scanf("%ld",&value.l);
    addEntry(key,value,&tab);
    break;
  case 3:
    printf("Nhap Ten:");
    gets(s);
    key=new_jval_s(s);
    ptr=getEntry(key,tab);
    if(jval_v(ptr)==NULL)
      printf("Khong tim thay\n");
    else{
      printf("Gia tri cua %s la %ld\n",key.s,ptr.l);
    }
    break;
  case 0:
    printf("thoat\n");
    dropSymbolTable(&tab);
    break;
  default :
    printf("Nhap lieu sai. Vui long nhap lai\n");
    break;
  }
  
  }while(c!=0);
  
  return 0;  
}
