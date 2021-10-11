#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers
char* result;

void init_regs();
bool interpret(char* instr);
bool compare_strings(char* str1, char* str2);
void calculate(int expression, char *registers[]);
char **tokenizer(char* string, char* delimeter);

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	int user_choice;
	int i = 0;
	char *instructions[] = {"LW","SW","ADD","ADDI"};
	bool is_opcode_match;
	

	char **tokens = tokenizer(instr, " ");

	for (i = 0; i < 4; i++){
		is_opcode_match = compare_strings(instructions[i],tokens[0]);
		if (is_opcode_match){
			user_choice = i;
			break;
		}	
		
	}
	calculate(user_choice, tokens);
	
	return true;
}


char **tokenizer(char* string, char* delimeter){
	char** tokens = malloc(4*sizeof(char*));
	char *token;
	int i = 0;
	token = strtok(string, delimeter);
	while(token != NULL){
		tokens[i] = token;
		token = strtok(NULL, delimeter);
		i++;
	}
	return tokens;
}


bool compare_strings(char str1[], char str2[]){
	int flag=0,i=0;
	while(str1[i]!='\0'||str2[i]!='\0'){
		if(str1[i]!=str2[i]){
			flag = 1;
			break;
		}
		i++;
	}
	if(flag==0){
		return true;
	}
	return false;
}


void calculate(int expression, char *registers[]){
	char *rd, *rs1, *rs2, *imm, *hex;
	char **address, **imm_index;
	int input1, input2, output;
	char file[] = "mem.txt";
	switch(expression){
		case 0:
			rd = registers[1]+1;
			rs1 = registers[2];
			address = tokenizer(rs1, "(");
			rs1 = address[0];
			imm = address[1];
			imm_index = tokenizer(imm,")");
			imm = imm_index[0]+1;
			input1 = atoi(rs1);
			input2 = atoi(imm);
			output = atoi(rd);
			reg[output] = 1;
			int32_t data = read_address(input1+input2, file);
			reg[output] = data;
			break;
		case 1:
			rd = registers[1];
			rs1 = registers[2];
			address = tokenizer(rs1, "(");
			imm = address[1];
			imm_index = tokenizer(imm, "(");
			imm = imm_index[0]+1;
			input1 = atoi(rs1);
			input2 = atoi(imm);
			output = atoi(rd);
			write_address(output, input1+input2, file);
			break;
		case 2:
			rd = registers[1]+1;
			rs1 = registers[2]+1;
			rs2 = registers[3]+1;
			input1 = atoi(rs1);
			input2 = atoi(rs2);
			output = atoi(rd);
			reg[output] = reg[input1] + reg[input2];
			break;
		case 3:
			rd = registers[1]+1;
			rs1 = registers[2]+1;
			imm = registers[3];
			input1 = atoi(rs1);
			output = atoi(rd);
			reg[output] = reg[input1] + imm;
			printf("OUTPUT: %d\n",reg[5]);
			break;

	}
}


int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE


	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");

	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}
