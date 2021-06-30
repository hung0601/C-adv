#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

void do_print();
void do_add(char *dn, char *ip);
void do_remove(char *dn);
void do_lookup_ip(char *dn);
void do_lookup_dn(char *ip);

int main(int argc, char **argv) {
  if (argc <= 1) {
    printf("Usage: prog print \n       prog add [dn] [ip] \n       prog remove [dn]\n       prog ip [dn]\n       prog dn [ip]\n");
    return 0;
  }

  if (strcmp(argv[1], "print") == 0) {
    if (argc != 2) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_print();
    return 0;
  }
  if (strcmp(argv[1], "add") == 0) {
    if (argc != 4) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_add(argv[2], argv[3]);
    return 0;
  }
  if (strcmp(argv[1], "remove") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_remove(argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "ip") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_ip(argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "dn") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_dn(argv[2]);
    return 0;
  }
  printf("Invalid parameters\n");
  return 0;
}

void print_entry(char *dn, char *ip) {
  printf("%s => %s\n", dn, ip);  
}


void do_print() {
  JRB i,tree=make_jrb();
  int n,index=0;
  FILE * f;
  char s[100];
  char s1[100],s2[100];
  f=fopen("dns.txt","r");
  if(f==NULL) {
    printf("error\n");
    return;
  }
  fscanf(f,"%d",&n);
  fgets(s,100,f);
  while(fgets(s1,100,f)!=NULL){
    index++;
    if(fgets(s2,100,f)==NULL){
      printf("error\n");
      return;
    }
    s1[strlen(s1)-1]='\0';
    if(index!=n) s2[strlen(s2)-1]='\0';
    jrb_insert_str(tree,strdup(s1),new_jval_s(strdup(s2)));

  }
  if(index!=n) {
    printf("error\n");
    return;
  }
  fclose(f);
  jrb_traverse(i,tree){
    print_entry(jval_s(i->key),jval_s(i->val));
  }
  jrb_free_tree(tree);
  return;
}

void do_add(char *dn, char *ip) {
  JRB i,tree=make_jrb();
  FILE * f;
  char s[100];
  char s1[100],s2[100];
  JRB find;
  int index=0,i2=0,n;
  f=fopen("dns.txt","r");
  if(f==NULL) {
    printf("error\n");
    return;
  }
  fscanf(f,"%d",&n);
  fgets(s,100,f);
  while(fgets(s1,100,f)!=NULL){
    index++;
    if(fgets(s2,100,f)==NULL){
      printf("error\n");
      return;
    }
    s1[strlen(s1)-1]='\0';
    if(index!=n) s2[strlen(s2)-1]='\0';
    jrb_insert_str(tree,strdup(s1),new_jval_s(strdup(s2)));
  }
  if(index!=n) {
    printf("error\n");
    return;
  }
  find=jrb_find_str(tree,dn);
  if(find==NULL) {
    jrb_insert_str(tree,strdup(dn),new_jval_s(strdup(ip)));
    index++;
  }
  else find->val=new_jval_s(strdup(ip));
  jrb_traverse(i,tree){
    print_entry(jval_s(i->key),jval_s(i->val));
  }
  fclose(f);
  f=fopen("dns.txt","w+");
  if(f==NULL) {
    printf("error\n");
    return;
  }
  fprintf(f,"%d\n",index);
  jrb_traverse(i,tree){
    i2++;
    fprintf(f,"%s\n",jval_s(i->key));
    if(i2==index) fprintf(f,"%s",jval_s(i->val));
    else fprintf(f,"%s\n",jval_s(i->val));
  }
  fclose(f);
  jrb_free_tree(tree);
  return;
}

void do_remove(char *dn) {
  JRB i,tree=make_jrb();
  FILE * f;
  char s[100];
  char s1[100],s2[100];
  JRB find;
  int index=0,i2=0,n;
  f=fopen("dns.txt","r");
  if(f==NULL) {
    printf("error\n");
    return;
  }
  fscanf(f,"%d",&n);
  fgets(s,100,f);
  while(fgets(s1,100,f)!=NULL){
    index++;
    if(fgets(s2,100,f)==NULL){
      printf("error\n");
      return;
    }
    s1[strlen(s1)-1]='\0';
    if(index!=n) s2[strlen(s2)-1]='\0';
    jrb_insert_str(tree,strdup(s1),new_jval_s(strdup(s2)));
  }
  if(index!=n) {
    printf("error\n");
    return;
  }
  find=jrb_find_str(tree,dn);
  if(find!=NULL) {
    jrb_delete_node(find);
    index--;
  }
  jrb_traverse(i,tree){
    print_entry(jval_s(i->key),jval_s(i->val));
  }
  fclose(f);
  f=fopen("dns.txt","w+");
  if(f==NULL) {
    printf("error\n");
    return;
  }
  fprintf(f,"%d\n",index);
  jrb_traverse(i,tree){
    i2++;
    fprintf(f,"%s\n",jval_s(i->key));
    if(i2==index) fprintf(f,"%s",jval_s(i->val));
    else fprintf(f,"%s\n",jval_s(i->val));
  }
  fclose(f);
  jrb_free_tree(tree);
  return;
}

void do_lookup_ip(char *dn) {
  JRB i,tree=make_jrb();
  FILE * f;
  char s[100];
  char s1[100],s2[100];
  JRB find;
  int index=0,i2=0,n;
  f=fopen("dns.txt","r");
  if(f==NULL) {
    printf("error\n");
    return;
  }
  fscanf(f,"%d",&n);
  fgets(s,100,f);
  while(fgets(s1,100,f)!=NULL){
    index++;
    if(fgets(s2,100,f)==NULL){
      printf("error\n");
      return;
    }
    s1[strlen(s1)-1]='\0';
    if(index!=n) s2[strlen(s2)-1]='\0';
    jrb_insert_str(tree,strdup(s1),new_jval_s(strdup(s2)));
  }
  if(index!=n) {
    printf("error\n");
    return;
  }
  find=jrb_find_str(tree,dn);
  if(find==NULL) printf("not found\n");
  else print_entry(jval_s(find->key),jval_s(find->val));
  fclose(f);
  jrb_free_tree(tree);
  return;
}

void do_lookup_dn(char *ip) {
  JRB i,tree=make_jrb();
  FILE * f;
  char s[100];
  char s1[100],s2[100];
  JRB find;
  int index=0,i2=0,n;
  int dau=0;
  f=fopen("dns.txt","r");
  if(f==NULL) {
    printf("error\n");
    return;
  }
  fscanf(f,"%d",&n);
  fgets(s,100,f);
  while(fgets(s1,100,f)!=NULL){
    index++;
    if(fgets(s2,100,f)==NULL){
      printf("error\n");
      return;
    }
    s1[strlen(s1)-1]='\0';
    if(index!=n) s2[strlen(s2)-1]='\0';
    jrb_insert_str(tree,strdup(s1),new_jval_s(strdup(s2)));
  }
  if(index!=n) {
    printf("error\n");
    return;
  }
  jrb_traverse(i,tree){
    if(strcmp(ip,jval_s(i->val))==0) {
      print_entry(jval_s(i->key),jval_s(i->val));
      dau++;
    }
  }
  if(dau==0) printf("not found\n");
  fclose(f);
  jrb_free_tree(tree);
  return;
}
