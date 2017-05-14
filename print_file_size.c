#include<stdio.h>
#include<stdlib.b>


int main(){
	char * name = "test.txt";
	int size = 0;
	FILE * fp;
	fp = fopen(name, "r");
	while (fgetc(fp) != EOF){
		size++;
	}
	printf("File \"%s\" size is: %d\n", name, size); 
	exit(0);




}
