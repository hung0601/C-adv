#include <stdio.h>
#include <string.h>
#include "graphjrb.h"
typedef struct station {
  int number;
  char name[30];
}station;
int main(){
  int i=0,j,output[10],stsize,outputsize;
  char s1[30],s2[30];
  station Station_name[20];
  Graph metro=createGraph();
  FILE *f;
  f=fopen("metrolines.txt","r");
  fgets(s1,30,f);
  do{
    fscanf(f,"%s",s1);
    if(strcmp(s1,"[LINES]")==0) break;
    fgets(s2,2,f);
    fgets(s2,30,f);
    s2[strlen(s2)-1]='\0';
    Station_name[i].number=s1[1]-48;
    strcpy(Station_name[i].name,s2);
    i++;
    stsize=i;
  }while(1);
  do{
    i=fscanf(f,"%s",s1);
    if(i==EOF) break;
    if(s1[0]!='M'&& s2[0]!='M'&& !adjecent(metro,s2[1]-48,s1[1]-48)) addEdge(metro,s2[1]-48,s1[1]-48);
    strcpy(s2,s1);
  }while(1);
  printf("Nhap Ga  muon tim lan can:");
  gets(s1);
  for(i=0;i<stsize;i++){
    if(!strcmp(s1,Station_name[i].name)) {
      outputsize=getAdjacentVertices(metro,Station_name[i].number,output);
    }
  }
  printf("Cac Ga lan can voi %s la:\n",s1);
  for(i=0;i<outputsize;i++)
    for(j=0;j<stsize;j++){
      if(output[i]==Station_name[j].number) printf("%s\n",Station_name[j].name);
      }
  fclose(f);
  return 0;

}
