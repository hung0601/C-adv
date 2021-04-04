#include "jval.h"
#include <stdio.h>
#include <string.h>
int main(){
  char s[80];
  Jval j,i;
  printf("Nhp:");
  gets(s);
  j=new_jval_s(s);
  printf("Nhp:");
  gets(s);
  i=new_jval_s(s);
  printf("%s%s\n",jval_s(j),jval_s(i));
  return 0;
}
