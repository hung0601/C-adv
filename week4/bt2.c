#include <stdio.h>
#include "fields.h"
#include "jval.h"
#include "jrb.h"
#include <string.h>
int compare_str_jval(Jval a,Jval b){
  return strcmp(jval_s(a),jval_s(b));
}
void addEntry(JRB tree, Jval key, Jval val, int (*func)(Jval,Jval)) {
  JRB ptr=jrb_find_gen(tree, key,func);
  if(ptr==NULL)
    jrb_insert_gen(tree,key,val,func);
  else{
    ptr->val=val;
  }
  return;
}
int main() {
  char s[80];
  int c;
  JRB pb,bn;
  Jval key,value;
  pb=make_jrb();
  do{
  printf("Chuong trinh phonebook\n");
  printf("1.In phonebook\n");
  printf("2.Them phone node\n");
  printf("3.Tim Phonenode\n");
  printf("0.Thoat\n");
  printf("Nhap lua chon:");
  scanf("%d%*c",&c);
  switch(c){
  case 1:
    jrb_traverse(bn, pb) {
      printf("%-20s%-10ld\n", bn->key.s,bn->val.l);
    }
    break;
  case 2:
    printf("Nhap Ten:");
    gets(s);
    key=new_jval_s(s);
    printf("Nhap sdt:");
    scanf("%ld",&value.l);
    addEntry(pb,key,value,compare_str_jval);
    break;
  case 3:
    printf("Nhap Ten:");
    gets(key.s);
    JRB ptr=jrb_find_gen(pb, key,compare_str_jval);
    if(ptr==NULL)
      printf("Khong tim thay\n");
    else{
      printf("Gia tri cua %s la %ld\n",ptr->key.s,ptr->val.l);
    }
    break;
  case 0:
    printf("thoat\n");
    break;
  default :
    printf("Nhap lieu sai. Vui long nhap lai\n");
    break;
  }
  
  }while(c!=0);
  
  return 0;  
}
