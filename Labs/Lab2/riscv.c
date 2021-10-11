#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

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
  char **token = tokenize(instr);

  char *first[] =  {"LW", "SW", "ADDI", "ADD"};
  int check_instr;
  char *instruction[1];
  char *reg1[1];

  int size_first = sizeof(first)/sizeof(first[0]);

  //find instruction
  for(int i = 0; i < size_first; i++){
    check_instr = strcmp(token[0], first[i]);
    if(check_instr == 0){
      instruction[0] = first[i];
      break;
    }
  }

  //Instruction = LW or SW
  if(instruction[0] == "LW" || instruction[0] == "SW"){
    //first register, remove "X"
    char *xOut = strtok(token[1], "X");
    int32_t reg_first = atoi(xOut);

    //immediate, number before second register
    int32_t imm = atoi(token[2]);

    //second register, remove "X"
    char *xOut2 = strtok(token[3], "X"); 
    int32_t reg_2 = atoi(xOut2);

    //Instruction is LW
    if(instruction[0] == "LW"){
      int32_t address = reg[reg_2] + imm;
      int32_t hold = read_address(address, "mem.txt");
      reg[reg_first] = hold;
    }

    //Instruction is SW
    if(instruction[0] == "SW"){
      int32_t address = imm + reg[reg_2];
      write_address(reg[reg_first], address, "mem.txt");
    }
  }

  //first register, remove "X"
  char *xOut = strtok(token[1], "X");
  int reg_first = atoi(xOut);

  //Instruction is "ADD"
  if(instruction[0] == "ADD"){

    //second register, we remove 'X' from string
    char *xOut2 = strtok(token[2], "X"); 
    int reg_sec = atoi(xOut2); 
    
    //third register, we remove 'X' from string
    char *xOut3 = strtok(token[3], "X"); 
    int reg_third = atoi(xOut3);

    //add 2nd and 3rd registers and store in 1st register
    reg[reg_first] = reg[reg_sec] + reg[reg_third];
  }

  //Instruction is "ADDI"
  if(instruction[0] == "ADDI"){

    //second register, we remove 'X' from string
    char *xOut2= strtok(token[2], "X"); 
    int reg_sec = atoi(xOut2);
    
    //add 2nd register and immediate store in 1st register
    reg[reg_first] = reg[reg_sec] + atoi(token[3]);
  }
  
  free(token);
	return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

  print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();

  printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");

	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}
