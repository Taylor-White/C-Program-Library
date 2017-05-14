#include<stdio.h>

int main(){
	int max = 1 << sizeof(char) * 8;
	int i;
	for(i=0; i < max; i++){
		printf("number %d: %c\n", i, i);
	}
	return 1;
}	
