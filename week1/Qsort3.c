#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#define Maxsize 10000000
#define Max 10
int int_compare(void const * x, void const *y) {
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
void sort3wayG(void* a, int size, int l, int r,int (*compare)(void const *, void const*)) {
  if (r <= l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1)
    {
      while ( compare(a+(++i)*size,a+r*size) < 0 );
      while (compare(a+r*size,a+(--j)*size) < 0 )
        if (j == l) break;
      if (i >= j) break;
      exch1(a, size, i, j);
      if (compare(a+i*size,a+r*size)==0)
        exch1(a, size, ++p, i);
      if (compare(a+j*size,a+r*size)==0)
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
void sort3way(int a[], int l, int r) {
  if (r <= l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1)
    {
      while (a[++i] < a[r]);
      while (a[r] < a[--j]) if (j == l) break;
      if (i >= j) break;
      exch(a, i, j);
      if (a[i]==a[r]) exch(a, ++p, i);
      if (a[j]==a[r]) exch(a, --q, j);
    }
  exch(a, i, r);
  j = i - 1;
  i = i + 1;
  for (int k = l ; k <= p; k++) exch(a, k, j--);
  for (int k = r-1; k >= q; k--) exch(a, k, i++);
  sort3way(a, l, j);
  sort3way(a, i, r);
}
void sort2way(int a[], int l, int r) {
  if (r <= l) return;
  int i = l-1, j = r;
  while(1)
    {
      while (a[++i] < a[r]);
      while (a[r] < a[--j]) if (j == l) break;
      if (i >= j) break;
      exch(a, i, j);
    }
  exch(a, i, r);
  j = i - 1;
  i = i + 1;
  sort2way(a, l, j);
  sort2way(a, i, r);
}

int main(){
  int *a1=(int*)malloc(Maxsize*sizeof(int));
  int *a2=(int*)malloc(Maxsize*sizeof(int));
  int *a3=(int*)malloc(Maxsize*sizeof(int));
  int *a4=(int*)malloc(Maxsize*sizeof(int));
  int *a5=(int*)malloc(Maxsize*sizeof(int));
  int i;
  struct timeval start,finish;
  srand(time(NULL));
  for(i=0;i<Maxsize;i++){
    a1[i]=rand()%Max;
    a2[i]=a1[i];
    a3[i]=a1[i];
    a4[i]=a1[i];
    a5[i]=a1[i];
  }
  gettimeofday(&start, NULL);
  sort2way(a1, 0,Maxsize-1);
  gettimeofday(&finish,NULL);
  printf("Sort2way took %ld micro seconds\n",(-start.tv_sec+finish.tv_sec)*1000000 + (-start.tv_usec+finish.tv_usec));

  gettimeofday(&start, NULL);
  sort3way(a2, 0,Maxsize-1);
  gettimeofday(&finish,NULL);
  printf("Sort3way took %ld micro seconds\n",(-start.tv_sec+finish.tv_sec)*1000000 + (-start.tv_usec+finish.tv_usec));

  gettimeofday(&start, NULL);
  sort2wayG(a3,sizeof(int),0,Maxsize,int_compare);
  gettimeofday(&finish,NULL);
  printf("sort2way generic function took %ld micro seconds\n",(-start.tv_sec+finish.tv_sec)*1000000 + (-start.tv_usec+finish.tv_usec));

  gettimeofday(&start, NULL);
  sort3wayG(a4,sizeof(int),0,Maxsize,int_compare);
  gettimeofday(&finish,NULL);
  printf("sort3way generic function took %ld micro seconds\n",(-start.tv_sec+finish.tv_sec)*1000000 + (-start.tv_usec+finish.tv_usec));

  gettimeofday(&start, NULL);
  qsort(a5,Maxsize,sizeof(int),int_compare);
  gettimeofday(&finish,NULL);
  printf("qsort took %ld micro seconds\n",(-start.tv_sec+finish.tv_sec)*1000000 + (-start.tv_usec+finish.tv_usec));

  free(a1);
  free(a2);
  free(a3);
  free(a4);
  free(a5);
  return 0;
}
