#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
int main(){
  char in[20]="input.txt";
  char out[20]="output.txt";
  compressFile(in,out);
  return 0;
}
