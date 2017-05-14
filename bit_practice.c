#include<stdio.h>
#include<stdlib.h>


// Function prototypes
void print_decimal_to_hex(int input);
void binary_string_to_decimal(char * input, unsigned int *result);
void decimal_string_to_decimal(char * input, unsigned int *result);
void print_decimal_to_binary_string(unsigned int result);
unsigned int decimal_mod_bit_at(unsigned int decimal, unsigned int index, int type);
void is_power_of_two(unsigned int input);
void is_power_of_two_one_line(unsigned int input);
void binary_swap(unsigned int * a, unsigned int * b);

typedef enum {false, true} bool;

#define SET 0
#define CLEAR 1
#define FLIP 2

int main(){

	unsigned int int_input_1;
	unsigned int int_input_2;
	printf("starting....\n");

	char input_one[80];
	char input_two[80];

	char operator;
	
	bool repeat = true;
	char * tasks[] = {
	"0: Quit",
	"1: Binary to decimal",
	"2: Binary to hex",
	"3: Decimal to hex",
	"4: Negate binary (~)",
	"5: And binary (&)",
	"6: XOR binary (^)",
	"7: OR binary (|)",
	"8: Binary Shift Left (negative numbers fail)",
	"9: Binary Shift Right (negative numbers fail)",
	"10: Binary, set bit at... (first bit is 0)",
	"11: Binary, clear bit at... (first bit is 0)",
	"12: Binary, flip bit at... (first bit is 0)",
	"13: Binary, check if a number is a power of 2",
	"14: Binary, check if a number is a power of 2 in one line",
	"15: Binary addition",

	NULL
	};
	int cur_task;

	while(repeat == true){
		printf("Choose a task: \n");
		int i=0;
		while(tasks[i] != NULL){
			printf("%s\n", tasks[i]);
			i++;
		}
		scanf(" %d", &cur_task);
		printf("You chose: %s\n", tasks[cur_task]);
		switch(cur_task){
			/* NOTE: The cases have a lot of repetative functionality.  They should be abstracted.  For example, create a function which inputs the number and type of inputs and operator to be applied to them.  */
			case 0:
				repeat= false;
				break;
			case 1: 
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("Decimal: %d\n\n", int_input_1);
				break;
			case 2:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				print_decimal_to_hex(int_input_1);
				break;
				
			case 3:
				printf("Input a decimal number: \n");
				scanf("%s", input_one);
				decimal_string_to_decimal(input_one, &int_input_1);
				print_decimal_to_hex(int_input_1);
				break;
			case 4:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);
				
				int_input_1 = ~int_input_1;
				printf("result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
			case 5:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);

				printf("Input another binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_2);
				printf("result: %u\n", int_input_2);

				int_input_1 = int_input_1 & int_input_2;
				printf("result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
			case 6:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);
				
				printf("Input another binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_2);
				printf("result: %u\n", int_input_2);

				int_input_1 = int_input_1^int_input_2;
				printf("result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
			case 7:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);
				
				printf("Input another binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_2);
				printf("result: %u\n", int_input_2);
				
				int_input_1 = int_input_1|int_input_2;
				printf("result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
			case 8:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);
				
				printf("How far do you want to shift?: \n");
				scanf("%u", &int_input_2);
				int_input_1 = int_input_1 << int_input_2;
				printf("Decimal result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
			case 9:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);
				
				printf("How far do you want to shift?: \n");
				scanf("%u", &int_input_2);
				int_input_1 = int_input_1 >> int_input_2;
				printf("Decimal result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
			case 10:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);
				
				printf("Which bit do you want to set?: \n");
				scanf("%u", &int_input_2);
				int_input_1 = decimal_mod_bit_at(int_input_1, int_input_2, SET);
				printf("Decimal result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
			case 11:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);
				
				printf("Which bit do you want to set?: \n");
				scanf("%u", &int_input_2);
				int_input_1 = decimal_mod_bit_at(int_input_1, int_input_2, CLEAR);
				printf("Decimal result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
			case 12:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				printf("result: %u\n", int_input_1);
				
				printf("Which bit do you want to set?: \n");
				scanf("%u", &int_input_2);
				int_input_1 = decimal_mod_bit_at(int_input_1, int_input_2, FLIP);
				printf("Decimal result: %u\n", int_input_1);
				print_decimal_to_binary_string(int_input_1);
				break;
				
			case 13:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				is_power_of_two(int_input_1);
				break;
			case 14:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				binary_string_to_decimal(input_one, &int_input_1);
				is_power_of_two_one_line(int_input_1);
				break;
			case 15:
				printf("Input a binary number: \n");
				scanf("%s", input_one);
				printf("Input a binary number: \n");
				scanf("%s", input_two);
				binary_string_to_decimal(input_one, &int_input_1);
				binary_string_to_decimal(input_two, &int_input_2);
				binary_swap(&int_input_1, &int_input_2);
				printf("Results: %d, %d\n", int_input_1,int_input_2);
			default:
				printf("Invalid input\n");
				repeat = false;
				break;
		}
		printf("\n");
	}
	return(0);
}

void print_decimal_to_binary_string(unsigned int decimal){
	const int INT_SIZE = 32;
	int bit_index;
	long power_of_two;

	char * output_str = malloc(sizeof(char) * ( INT_SIZE + 1 ));
	if(output_str == NULL){
		//TODO: Print the errno
		printf("Not enough memory for malloc\n");
		return;
	}	

	char * pr = output_str;
	power_of_two=1;
	bit_index=0;
	while(power_of_two <= decimal){
		power_of_two = power_of_two << 1;
		bit_index++;
	}
	power_of_two = power_of_two >> 1;
	bit_index--;
	for(int z=0; z < (INT_SIZE - bit_index - 1); z++,pr++){
		*pr = '0';
	}

	while(bit_index >= 0){
		if(power_of_two <= decimal){
			*pr='1';
			decimal = decimal - power_of_two;
		}else{
			*pr = '0';
		}
		power_of_two = power_of_two >> 1;
		bit_index--;
		pr++;
	}
	*pr = '\0';

	printf("Binary result: %s\n", output_str);
	free(output_str);
	output_str = NULL;
}	

void binary_string_to_decimal(char * input, unsigned int * result){

	int digit;
	*result = 0;
	int exponent = 0;
	while(*input){
		int i = (int)(*input-'0');
		if(i != 1){i = 0;}
		int digit = i;
		*result = (*result << 1 ) + digit;
		exponent++;
		input++;
	}
}

void decimal_string_to_decimal(char * input, unsigned int *result){
	*result = 0;
	while(*input){
		int i = (int)(*input-'0');
		if(i > 9 || i < -9){i = 0;}
		*result = *result * 10 + i;
		input++;
	}
}

void print_decimal_to_hex(int input){
	printf(" 0x%08x\n", input);
}

unsigned int decimal_mod_bit_at(unsigned int decimal, unsigned int index, int type){
	unsigned int bit = 0;
	if(index < 1){return(decimal);}
	bit = 1 << index;
	if(type == SET){
		return(bit | decimal);
	}else if(type == CLEAR){
		return(bit & decimal);

	}else if(type == FLIP){
		return(bit ^ decimal);

	}else{
		printf("ERROR: Invalid Modifying Type");
		return (-1);
	}
}

void is_power_of_two(unsigned int input){
	int x = 1;
	int len = sizeof(int)*8;
	while(x < len){
		if(x == input){
			printf("result:  %d is a power of 2\n", input);
			return;
		}
		x <<= 1;
	}
	printf("result: %d is not a power of 2\n", input);
}
void is_power_of_two_one_line(unsigned int input){
	if(input && !(input&(input-1))){
		printf("result:  %d is a power of 2\n", input);
	}else{
		printf("result: %d is not a power of 2\n", input);
	}
}


void binary_swap(unsigned int * a, unsigned int * b){
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
