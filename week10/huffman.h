#include <stdio.h>
typedef struct htree{
  int size;
  char s;
  struct htree * left;
  struct htree * right;
}htree;
typedef struct {
  int size;
  char bits[20];
} Coding;
typedef struct {
  int i;
  int size;
  int * nodes;
}HuffmanTreeArray;
int treeHight(htree *htree);
HuffmanTreeArray initHarray(htree *h);
void  htree2array(htree* h,HuffmanTreeArray *array);
htree * merge_htree(htree * h1,htree * h2 );
htree * make_htree(char * buffer,int size);
void createHuffmanTable(htree*  htree, Coding* htable);
void compressFile(char* in, char *out);
void decompressFile(char * out1, char *out2);
void htree_free_tree(htree * h);
