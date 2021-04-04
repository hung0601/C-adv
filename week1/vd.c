#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int int_compare(void const * x, void const*y) {
  int m, n;
  m = *((int*)x);
  n = *((int*)y);
  if ( m == n ) return 0;
  return m > n ? 1: -1;
}
void exch1(void*a,int size,int i,int j){
  void *temp=(void*)malloc(size);
  memcpy(temp,a+i*size,size);
  memcpy(a+i*size,a+j*size,size);
  memcpy(a+j*size,temp,size);
  free(temp);
  return;
}
void sort2wayG(void* a, int size, int l, int r,int (*compare)(void const*, void const*)) {
  if (r <= l) return;
  int i = l-1, j = r;
  while(1)
    {
      while ( compare(a+(++i)*size,a+r*size) < 0 );
      while (compare(a+r*size,a+(--j)*size) < 0 )
        if (j == l) break;
      if (i >= j) break;
      exch1(a, size, i, j);
    }
  exch1(a, size, i, r);
  j = i - 1;
  i = i + 1;
  sort2wayG(a, size, l, j, compare);
  sort2wayG(a, size, i, r, compare);
}
void exch(int a[],int i,int j){
  int k;
  k=a[i];
  a[i]=a[j];
  a[j]=k;
  return;
}
void sort3wayG(void* a, int size, int l, int r,int (*compare)(const void*,const void*)) {
  if (r <= l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1)
    {
      while ( compare((char*)a+(++i)*size, (char*)a+r*size) < 0 );
      while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0 )
        if (j == l) break;
      if (i >= j) break;
      exch1(a, size, i, j);
      if (compare((char*)a+i*size, (char*)a+r*size)==0)
        exch1(a, size, ++p, i);
      if (compare((char*)a+j*size, (char*)a+r*size)==0)
        exch1(a, size, --q, j);
    }
  exch1(a, size, i, r);
  j = i - 1;
  i = i + 1;
  for (int k = l ; k <= p; k++) exch1(a, size, k, j--);
  for (int k = r-1; k >= q; k--) exch1(a, size, k, i++);
  sort3wayG(a, size, l, j, compare);
  sort3wayG(a, size, i, r, compare);
}
int main(){
  int A[10]={1,28,5,1,2,10,15,10,1,10};
  int i;
  for(i=0;i<10;i++){
    printf("%d  ",A[i]);
  }
  printf("\n");
  sort2wayG(A,sizeof(int),0,9,int_compare);
  //qsort(A,10,sizeof(int),int_compare);
  for(i=0;i<10;i++){
    printf("%d  ",A[i]);
  }
  printf("\n");
  return 0;
}
