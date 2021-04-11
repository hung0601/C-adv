#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"
int main(){

  BTA * pb;
  btinit();
  char pbname[30],name[ZKYLEN];
  int c,i=0;
  BTint val;
  do{
  printf("----------------------------------------------\n");
  printf("Chuong trinh phonebook\n");
  printf(" 1.Tao/mo phonebook\n");
  printf(" 2.Them phonenode\n");
  printf(" 3.Tim Phonenode\n");
  printf(" 4.Xoa\n");
  printf(" 5.In phonebook\n");
  printf(" 0.Thoat\n");
  printf("Nhap lua chon:");
  scanf("%d%*c",&c);
  printf("----------------------------------------------\n");
  switch(c){
  case 1:
    if(i>0) btcls(pb);
    i++;
    printf("Nhap ten phonebook:");
    gets(pbname);
    pb=btopn(pbname,0,FALSE);
    if(pb==NULL){
      pb=createPhoneBook(pbname);
    }
    break;
  case 2:
    printf("Nhap Ten:");
    gets(name);
    printf("Nhap sdt:");
    scanf("%d",&val);
    addPhoneNumber(pb,name,val);
    break;
  case 3:
    printf("Nhap Ten:");
    gets(name);
    val=getPhoneNumber(pb,name);
    if(val>=0) printf("%s: %d\n",name,val);
    else printf("Khong tim thay\n");
    break;
  case 4:
    printf("Nhap Ten:");
    gets(name);
    bdelky(pb,name);
    break;
  case 5:
    PrintPhoneBook(pb);
    break;
  case 0:
    printf("thoat\n");
    btcls(pb);
    break;
  default :
    printf("Nhap lieu sai. Vui long nhap lai\n");
    break;
  }

  }while(c!=0);
  return 0;
}
