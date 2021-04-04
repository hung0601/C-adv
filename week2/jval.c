#include <stdio.h>
#include "jval.h"
#include <stdlib.h>
#include <time.h>
#define Max 100
int Jval_compare_i(Jval a,Jval b){
  if (jval_i(a)>jval_i(b)) return 1;
  else if (jval_i(a)==jval_i(b)) return 0;
  else return -1;
}
void exch_jval(Jval a[],int i, int j){
  Jval temp;
  temp=a[i];
  a[i]=a[j];
  a[j]=temp;
}
void sort_jval(Jval a[],int l, int r,int (*compare)(Jval , Jval)) {
  if (r <= l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1)
    {
      while ( compare(a[++i],a[r]) < 0 );
      while (compare(a[r],a[--j]) < 0 )
        if (j == l) break;
      if (i >= j) break;
      exch_jval(a, i, j);
      if (compare(a[i],a[r])==0)
        exch_jval(a, ++p, i);
      if (compare(a[j],a[r])==0)
        exch_jval(a, --q, j);
    }
  exch_jval(a, i, r);
  j = i - 1;
  i = i + 1;
  for (int k = l ; k <= p; k++) exch_jval(a, k, j--);
  for (int k = r-1; k >= q; k--) exch_jval(a, k, i++);
  sort_jval(a, l, j, compare);
  sort_jval(a, i, r, compare);
}
int search_jval(Jval a[],int l, int r,Jval item,int (*compare)(Jval,Jval)) {
  if (r < l) return -1;
  int i = (l + r)/2;
  int res;
  res = compare( item,a[i]);
  if (res==0)
    return i;
  else if (res < 0)
    return search_jval(a,l, i-1, item, compare);
  else
    return search_jval(a, i+1, r, item, compare);
}
int main(){
  Jval a[Max],key;
  int i;
  for(i=0;i<Max;i++){
    a[i]= new_jval_i(rand()%100);
  }
  sort_jval(a,0,Max-1,Jval_compare_i);
  printf("Nhap so ban muon tim:");
  scanf("%d",&key.i);
  i=search_jval(a,0,Max-1,key,Jval_compare_i);
  if(i>=0) printf("Tim thay so %d o vi tri %d\n",jval_i(key),i+1);
  else printf("Khong tim thay\n");
  for(i=0;i<Max;i++) printf("%d ",jval_i(a[i]));
  printf("\n");
  return 0;
}
