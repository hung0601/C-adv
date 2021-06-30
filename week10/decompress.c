#include <stdio.h>
#include "huffman.h"
int main(){
  char out1[30]="output.txt";
  char out2[30]="output2.txt";
  decompressFile(out1,out2);
  return 0;
}
