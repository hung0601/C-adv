#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ENTRY 1000

struct PhoneEntry {
  char number[10];
  char name[50];
}PhoneEntry;
typedef struct PhoneEntry *phonebook;
void read_from_file(struct PhoneEntry ds[],int *i){
  FILE *f;
  *i=0;
  char s[100];
  f=fopen("pb.dat","r");
  while(fgets(s,1,f)!=NULL){
    s[strlen(s)-1]='\0';
    strcpy(ds[*i].number,s);
    fgets(s,1,f);
    strcpy(ds[*i].name,s);
    (*i)++;
  }
  fclose(f);
  return;
}


int no_entries;
int main() {
  phonebook ds=(phonebook)malloc(sizeof(PhoneEntry));

  return 0;
}
