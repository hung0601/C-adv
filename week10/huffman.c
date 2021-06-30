#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "dllist.h"
#include "huffman.h"
htree * merge_htree(htree * h1, htree *h2){
  htree *root;
  root=(htree*)malloc(sizeof(htree));
  root->size= h1->size+h2->size;
  root->s=0;
  root->left=h1;
  root->right=h2;
  return root;
}
htree * make_htree(char * buffer,int size){
  FILE *f;
  Dllist q,ptr,n;
  htree *node,*left,*right,*root,*min;
  int m=0;
  char c;
  q=new_dllist();
  f=fopen(buffer,"r");
  while((c=fgetc(f))!= EOF){
    dll_traverse(ptr,q){
      node=(htree*)jval_v(ptr->val);
      if(node->s==c) {
        node->size++;
        m=1;
      }
    }
    if(m!=1){
      node=(htree*)malloc(sizeof(htree));
      node->s=c;
      node->size=1;
      dll_append(q,new_jval_v(node));
    }
    m=0;
  }
  fclose(f);
  while(!dll_empty(q)){
    n=dll_first(q);
    left=(htree*)jval_v(n->val);
    dll_traverse(ptr,q){
      node=(htree*)jval_v(ptr->val);
      if(node->size<left->size) {
        left=node;
        n=ptr;
      }
    }
    dll_delete_node(n);
    n=dll_first(q);
    right=(htree*)jval_v(n->val);
    dll_traverse(ptr,q){
      node=(htree*)jval_v(ptr->val);
      if(node->size<right->size) {
        right=node;
        n=ptr;
      }
    }
    dll_delete_node(n);
    if(dll_empty(q)) {
      return merge_htree(left,right);
      free_dllist(q);
    }
    root=merge_htree(left,right);
    dll_append(q,new_jval_v(root));
  }
}
void createHuffmanTable(htree*  htree, Coding* htable){
  if(htree->left!=NULL) {
    htable[0].bits[htable[0].size++]='0';
    createHuffmanTable(htree->left,htable);
    htable[0].size--;
  }
  if(htree->right!=NULL) {
    htable[0].bits[htable[0].size++]='1';
    createHuffmanTable(htree->right,htable);
    htable[0].size--;
  }
  if(htree->left==NULL && htree->right==NULL){
    htable[0].bits[htable[0].size]='\0';
    strcpy(htable[htree->s].bits,htable[0].bits);
    htable[htree->s].size=htable[0].size;
  }
}
int treeHight(htree *htree){
  int h=0;
  if (htree==NULL) return 0;
  else return 1+ (treeHight(htree->left)>treeHight(htree->right) ?  treeHight(htree->left):treeHight(htree->right));
}
HuffmanTreeArray  initHarray(htree *h){
  HuffmanTreeArray array;
  array.i=0;
  array.size=pow(2,treeHight(h))-1;
  array.nodes=(int*)malloc(sizeof(int)*array.size);
  return array;
}
void htree2array(htree* h,HuffmanTreeArray *array){
  if(h->s==0) array->nodes[array->i]=-1;
  else array->nodes[array->i]=h->s;
  if(h->left!=NULL){
    array->i=array->i*2+1;
    htree2array(h->left,array);
    array->i=(array->i-1)/2;
  }
  if(h->right!=NULL){
    array->i=array->i*2+2;
    htree2array(h->right,array);
    array->i=(array->i-1)/2;
  }
}
void compressFile(char * in,char *out){
  htree *h;
  HuffmanTreeArray  array;
  Coding htable[256];
  int i;
  char c;
  FILE *f1,*f2;
  for(i=0;i<256;i++) htable[i].size=0;
  h=make_htree(in,1);
  createHuffmanTable(h,htable);
  array=initHarray(h);
  htree2array(h,&array);
  f1=fopen(in,"r");
  f2=fopen(out,"a+");
  fprintf(f2,"HM\n");
  fprintf(f2,"%d\n",array.size);
  for(i=0;i<array.size;i++){
    fprintf(f2,"%d ",array.nodes[i]);
  }
  fprintf(f2,"\n");
  while((c=fgetc(f1))!=EOF){
    fprintf(f2,"%s",htable[c].bits);
  }
  fclose(f1);
  fclose(f2);
  htree_free_tree(h);
  free(array.nodes);
  return;
}

void decompressFile(char * out1, char * out2){
  int i,c;
  char s[10];
  FILE *f1,*f2;
  HuffmanTreeArray array;
  f1=fopen(out1,"r");
  f2=fopen(out2,"a+");
  fgets(s,10,f1);
  s[strlen(s)-1]='\0';
  if(strcmp(s,"HM")==0){
    fscanf(f1,"%d",&array.size);
    array.nodes=(int*)malloc(sizeof(int)*array.size);
    for(i=0;i<array.size;i++){
      fscanf(f1,"%d",&array.nodes[i]);
      // printf("%d ",array.nodes[i]);
    }
    fgets(s,10,f1);
    i=0;
    while((c=fgetc(f1))!=EOF){
      if(c=='0') i=i*2+1;
      if(c=='1') i=i*2+2;
      if(array.nodes[i]!=0 && array.nodes[i]!=-1) {
        fputc(array.nodes[i],f2);
        i=0;
      }
    }
  }
  fclose(f1);
  fclose(f2);
  free(array.nodes);
  return;
}

void htree_free_tree(htree* h){
  if(h->left!=NULL) htree_free_tree(h->left);
  if(h->right!=NULL) htree_free_tree(h->right);
  free(h);
  return;
}
