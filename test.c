#include <stdio.h>
#include <stdlib.h>
int main(){
	FILE * f;
	int i1,i2;
	f=fopen("test.txt","r");
	fscanf(f,"%d%d",&i1,&i2);
	printf("%d %d",i1,i2);
	i1=fgetc(f);
	printf("%c",i1);
	fclose(f);
	return 0;
}