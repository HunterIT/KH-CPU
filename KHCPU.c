t/**************************
* Name: KH-CPU.c
* Author: Kenneth Hunter
* URL: http://www.hunterit.ca
* Email: kenneth@hunterit.ca
* Course: Computer Architecture
* Last Revision: April, 26th, 2015
*
* Purpose: The following program is a virtual CPU based on 16k of memory.
* 			The purpose of this lab is to create the basic software to run
*          and control on a virtual realtime CPU. The software has
*          the functions that include
*  		  - Dump Memory
*            - Go (Run the entire loaded program
*            - Load a file into memory
*            - Modify Memory
*            - Display current registers
*            - Trace mode
*            - Write to a file in memory
*            - Reset the registers to zero position
***************************/

#include "khcpu.h"		//CPU Headers

/**************************************************
	The main is used to set-up the application by zeroing 
   the registers, displaying the initial help menu, 
   then displaying the user interface to type in
   the requested commands
*****************************************************/
int main(void) {

	/* All registers and flag will be set to ZERO */
	reset();
	/* Display intro text of the name and author of CPU*/
	intro();
	/* Display the Help Menu */
	displayOptions();
	/* Run the User Interface */
	userInterface();
	
	return 0;
}

/**
* Display Intro */
void intro() {

	printf("|*******************************|\n");
	printf("|      Welcome to KH-CPU        |\n");
	printf("|  Created by: Kenneth Hunter   |\n");
	printf("| please read docs for help! :) |\n");
	printf("|*******************************|\n\n");
}


/****************************************************************
* displayOptions
*
* This will display a list of commands the user can use on the CPU.
* this will be displayed at the start of the cpu, and the if the user
* request the it by using the ?, or h keys. As explained in the menu.
********************************************************************/
void displayOptions() {
	printf("Please select an option!\n\n");
	printf("d\t\t--Dump memory\n");
	printf("g\t\t--Go - run the entire program\n");
	printf("l\t\t--Load a file into memory\n");
	printf("m\t\t--Memory modify\n");
	printf("q\t\t--Quit program\n");
	printf("r\t\t--Display registers\n");
	printf("t\t\t--Trace - execute one instruction\n");
	printf("w\t\t--Write file\n");
	printf("z\t\t--Reset all registers to zero\n");
	printf("?, h\t\t--Display list of commands\n");
}

/****************************************************************
* userInterface()
*
* This function will be in a while loop until the user decides to 
* quit. The function will input the users commands and assign the
* function to its selected purpose
********************************************************************/
void userInterface() {

	unsigned char input[BUFFER_SIZE];
	int file_result;
	unsigned int offset, row_length; 
	unsigned char memory[MEMORY];

	while (1) {

		printf("\n$> ");
		fgets(input, BUFFER_SIZE, stdin);

		switch (input[0]) {
		case 'D':
		case 'd': printf("Select an Offset> ");
				  fscanf(stdin, "%X", &offset);
				  printf("Select a length> ");
			      fscanf(stdin, "%X", &row_length);
			      dump_memory(memory, (void *)offset, row_length);
			      getchar();
			      break;
		case 'G':
		case 'g': while (!stop_flag) 
					runCycle(memory);
				  break;
		case 'L':
		case 'l': if ((file_result = loadFile(memory, MEMORY)) > 0)
				  printf("The Loaded file has %d bytes that were read", file_result);
				  else printf("The file has failed to load");
				  break;
		case 'M':
		case 'm': printf("Select an Offset> ");
				  fscanf(stdin, "%X", &offset);
				  modify_memory(memory, offset);
				  getchar();
				  break;
		case 'Q':
		case 'q': printf("Goodbye, Thanks for using KH-CPU!\n");
				  exit(0);
				  break;
		case 'R':
		case 'r': dump_reg();
				  break;
		case 'T':
		case 't': runCycle(memory);
				  dump_reg();
				  break;
		case 'W':
		case 'w': writeFile(memory);
				  break;
		case 'Z':
		case 'z':
				  reset();
				  printf("All registers / Flags have been set to ZERO\n");
				  break;
		case '?':
		case 'H':
		case 'h': displayOptions();
				  break;
		default: printf("Nothing selected");
				 break;
		}
	}
}

/****************************************************************
* reset()
*
* This function resets all the registers and flag of the CPU to zero
* The use of the is to start at memory location 0 again to reload
* or trace though a problem. This is also used at the start of the
* program to zero everything so it doesn't generate random data.
********************************************************************/
void reset() {

	/* Reset setALUFlag */
	sign_flag = RESET;
	zero_flag = RESET;
	carry_flag = RESET;
	stop_flag = RESET;
	ir_flag = RESET;

	/* Registers */
	mar = RESET;
	mbr = RESET;
	ir = RESET;
	currentI = RESET;

	unsigned int i;

	/* All displayed registers */
	for (i = 0; i < 0x10; i++){
		registers[i] = RESET;
	}
}

/****************************************************************
* writeFile()
*
* This function allows the user to write a file with users choice
* of bytes to make it. The file will be filled with all zeros. The 
* file can be used to write future data into the CPU when you can
* load it in.
********************************************************************/
void writeFile(void * memory) {

	FILE *f;  //The File
	char flushInput[3]; //Flush the input 
	char name[BUFFER_SIZE];
	int num_bytes; //Number of Bytes
	int write_bytes; //Bytes that have been written

	//Ask the User for file name
	printf("\nEnter a File Name:");
	fgets(name, BUFFER_SIZE, stdin);

	//Make last byte NULL
	name[strlen(name) - 1] = '\0';

	//Ask the user the number of bytes to write
	printf("\nHow much bytes do you want to write?");
	scanf("%d", &num_bytes);
	fgets(flushInput, 3, stdin);

	//Open the File
	if ((f = fopen(name, "wb")) == NULL) {
		printf("\nFailed to open the file");
	}

	if ((write_bytes = fwrite(memory, 1, num_bytes, f)) < 0) {
		printf("Error: Could not write to file");
	}
	else {
		printf("There has been %d bytes that have been written\n", write_bytes);
	}

	return;
}

/****************************************************************
* int loadFile(unsigned int max)
*
* This function allows the user to load a file in the cpu virtual memory
* this is useful for running binary files and just for using the
* built in HeX edior for viewing the content. Only files under 16 bytes
* can be loaded into the CPU, due to the virtual memory allowed space.
********************************************************************/
int loadFile(void * memory, unsigned int max) {

	FILE *f;
	int size;  					//The file size
	char name[BUFFER_SIZE]; 	//Get the name of the file

	//Ask the user for the File Name/Type
	printf("File Name: ");
	fgets(name, BUFFER_SIZE, stdin);

	//Remove the last byte to NULL
	name[strlen(name) - 1] = '\0';

	//Test if you can open the file
	if ((f = fopen(name, "rb")) == NULL) {
		return -1;
	}

	fseek(f, 0, SEEK_END);

	size = ftell(f);

	//Test to see if the file is truncated        
	if (size > max) {
		printf("The selected file has been truncated\n");
		size = max;
	}

	//Set the file position to the start of the file
	rewind(f);

	return fread(memory, sizeof(char), size, f);
}

/****************************************************************
* dump_memory(unsigned int offset, unsigned int length)
*
* This function allows the user to dump the memory of the CPU. This
* is helpful to be used as a Hex Viewer of a file, or just to see
* the contents of the CPU.
********************************************************************/
void dump_memory(void * memory, unsigned int offset, unsigned int length){
	unsigned int i;
	unsigned int lineLength = 0x10;
	unsigned char line[0x10];
	unsigned int count = 0;

	while (count < length){

		if (offset == MEMORY){
			break;
		}

		//Print the Offset & Block Number
		printf("%4.4X\t", offset);


		// Create the line of the HEX Digits
		for (i = 0; i < 0x10; i++, offset++, count++){

			//*CHECKS* to see if the pointer is not going out of bounds
			if (offset == MEMORY){
				lineLength = i;
				break;
			}

			//*CHECKS* to see if it's staying the limited length
			if (count == length){
				lineLength = i;
				break;
			}

			line[i] = *((char*)memory + offset);
			printf("%2.2X ", line[i]);
		}
		printf("\n\t");


		//Next Line, PRINT OUT ASCII VALUES
		for (i = 0; i < lineLength; i++){
			if (isprint(line[i])){
				printf(" %c ", line[i]);  //Prints out ASCII if valid
			}
			else{
				printf(" . ");		//Prints out DOT if not valid
			}
		}
		//Do it Again.... 
		printf("\n");
	}
}

/****************************************************************
* dump_reg
*
* This function displays all the values in the Registers and setALUFlag.
* this is used in the trace commands and normal dump to view the 
* changes in the registers and different setALUFlag
********************************************************************/
int dump_reg(){
	unsigned int i;

	/* Print register file */
	for (i = 0; i < 0x10; i++){
		if (i % 0x6 == 0){
			printf("\n");
		}
		/* Stack Pointer */
		if (i == 0xD){
			printf(" SP:%08X ", SP);
		}
		/* Stack Pointer */
		else if (i == 0xE){
			printf(" LR:%08X ", LR);
		}
		/* Program Counter */
		else if (i == 0xF){
			printf(" PC:%08X ", PC);
		}
		else{
			printf("r%02d:%08X ", i, registers[i]);
		}
	}

	/* Print setALUFlag */
	printf("\t SZC:%d%d%d", sign_flag, zero_flag, carry_flag);

	/* Print non-visible registers */
	printf("\n   MAR:%08X   MBR:%08X   IR0:%04X   IR1:%04X   Stop:%0d   IR Flag:%01d\n", mar, mbr, IR0, IR1, stop_flag, ir_flag);

	return 0;
}


/********************************************************************
* Instruction Cycle:
* The instruction cycle keeping creating fetch of memory then 
* exciting the file depending on if needed a fetch for if the 
* Instructions register flag has been set.
***********************************************************************/
void runCycle(void * memory){

	//Check to see if the IR Flag is SET or NOT
	if (ir_flag == NOTSET){
		ir_flag = SET;

		//Fetch the next block of memory to run
		fetch(memory);

		//Saving the value of the current instruction into the IR register
		currentI = IR0;

		//Execute the instruction
		execute(memory);
	}
	else{

		//If the IR flag is not set you don't hvae to fetch, just excute
		ir_flag = NOTSET;
		currentI = IR1;
		execute(memory);
	}
}


/********************************************************
* Fetch:  
* The fetch command does one cycle at a time. It loads a the 
* memory in register to one at time.
**************************************************************/
void fetch(void * memory){

	ir = registerLoad(PC, memory);
	PC += REG_SIZE;
}

/***************************************************************
* Load Register: Load a register with memory at location of MAR.
*                MAR must be set before this function is called.
******************************************************************/
uint32_t registerLoad(uint32_t new_mar, void * memory){
	unsigned int i;
	mar = new_mar;
	for (i = 0; i < (REG_SIZE / BYTE_SIZE); i++, mar++){
		mbr = mbr << 8;
		mbr += *((unsigned char*)memory + mar);
	}
	return mbr;
}

/***************************************************************
* Store Register: Store an entire register into memory at MAR.
*
******************************************************************/
void registerSave(uint32_t new_mar, uint32_t new_mbr, void * memory){

	mar = new_mar;
	mbr = new_mbr;

	*((unsigned char*)memory + mar++) = 
		(unsigned char)(mbr >> 24 & 0xFF);
	*((unsigned char*)memory + mar++) = 
		(unsigned char)(mbr >> 16 & 0xFF);
	*((unsigned char*)memory + mar++) = 
		(unsigned char)(mbr >> 8 & 0xFF);
	*((unsigned char*)memory + mar) = 
		(unsigned char)mbr & 0xFF;
}

/***************************************************************
* Execute: Will run though the binary file and every instruction 
		   will be sorted into the right instruction requirments
		   depending on the where in the PC the process is currently
		   is
******************************************************************/
void execute(void * memory){
	int i;

	if (PROC){
		if (AND){
			setALUFlag(registers[RD] & registers[RN]);
			registers[RD] = registers[RD] & registers[RN];
		}
		else if (EOR){
			setALUFlag(registers[RD] ^ registers[RN]);
			registers[RD] = registers[RD] ^ registers[RN];
		}
		else if (SUB){
			setALUFlag(registers[RD] + ~registers[RN] + 1);
			carry_flag = checkIfCarry(registers[RD], ~registers[RN], 1);
			registers[RD] = registers[RD] + ~registers[RN] + 1;
		}
		else if (SXB){
			if ((registers[RN] & 0x80) == 1){
				registers[RN] += 0xFFFFFF00;
			}
			setALUFlag(registers[RN]);
			registers[RD] = registers[RN];
		}
		else if (ADD){
			setALUFlag(registers[RD] + registers[RN]);
			carry_flag = checkIfCarry(registers[RD], ~registers[RN], 0);
			registers[RD] = registers[RD] + registers[RN];
		}
		else if (ADC){
			setALUFlag(registers[RD] + registers[RN] + carry_flag);
			carry_flag = checkIfCarry(registers[RD], registers[RN], carry_flag);
			registers[RD] = registers[RD] + registers[RN] + carry_flag;
		}
		else if (LSR){
			for (i = 0; i < registers[RN]; i++){
				carry_flag = registers[RN] & 0x1;
				alu = registers[RD] >> 1;
			}
			setALUFlag(alu);
			registers[RD] = alu;
		}
		else if (LSL){
			for (i = 0; i < registers[RN]; i++){
				carry_flag = registers[RN] & 0x1;
				alu = registers[RD] << 1;
			}
			setALUFlag(alu);
			registers[RD] = alu;
		}
		else if (TST){
			setALUFlag(registers[RD] & registers[RN]);
		}
		else if (TEQ){
			setALUFlag(registers[RD] ^ registers[RN]);
		}
		else if (CMP){
			setALUFlag(registers[RD] + ~registers[RN] + 1);
			carry_flag = checkIfCarry(registers[RD], ~registers[RN], 1);
		}
		else if (ROR){
			for (i = 0; i < registers[RN]; i++){
				carry_flag = registers[RD] & 0x1;
				alu = registers[RD] >> 1;
				if (carry_flag){
					alu |= 0x80000000;
				}
			}
			setALUFlag(alu);
			registers[RD] = alu;
		}
		else if (ORR){
			setALUFlag(registers[RD] | registers[RN]);
			registers[RD] = registers[RD] | registers[RN];
		}
		else if (MOV){
			registers[RD] = registers[RN];
			setALUFlag(registers[RD]);
		}
		else if (BIC){
			setALUFlag(registers[RD] & ~registers[RN]);
			registers[RD] = registers[RD] & ~registers[RN];
		}
		else if (MVN){
			setALUFlag(~registers[RN]);
			registers[RD] = ~registers[RN];
		}
	}
	/*
	* The Load/Store Instructions!
	*/
	else if (LOAD_STORE){

		if (LOAD_BIT){
			/*Loading a Byte */
			if (BYTE_BIT){
				registers[RD] = registerLoad(registers[RN], memory);
				registers[RD] = registers[RD] & 8;
			}
			/*Loading in a Double Word */
			else
				registers[RD] = registerLoad(registers[RN], memory);
		}
		else{
			mbr = registers[RD];

			if (BYTE_BIT){
				mar = registers[RN];
				mbr = registers[RD];
				*((unsigned char*)memory + mar) = (unsigned char)mbr & 8;
			}
			else{
				registerSave(registers[RN], registers[RD], memory);
			}
		}
		/*
		* Immediate Instructions
		*/
	}
	else if (IMMEDIATE){
		/* Move immediate value into registers at RD */
		if (MOV){
			registers[RD] = IMM_VALUE;
			setALUFlag(registers[RD]);
		}
		else if (CMP){
			setALUFlag(registers[RD] + ~IMM_VALUE + 1);
			carry_flag = checkIfCarry(registers[RD], ~IMM_VALUE, 0);
		}
		else if (ADD){
			setALUFlag(registers[RD] + IMM_VALUE);
			carry_flag = checkIfCarry(registers[RD], IMM_VALUE, 0);
			registers[RD] = registers[RD] + IMM_VALUE;
		}
		else if (SUB){
			setALUFlag(registers[RD] + ~IMM_VALUE + 1);
			carry_flag = checkIfCarry(registers[RD], ~IMM_VALUE, 1);
			registers[RD] = registers[RD] + ~IMM_VALUE + 1;
		}
		/*
		* Conditional Branch
		*/
	}
	else if (COND_BRANCH){
		if (checkBranch()){
			alu = PC + (int8_t)COND_ADDR;

			if (ir_flag != 0){
				ir_flag = 0;
				alu = alu + ~0x2 + 1;
			}
			PC = alu;
		}
	}

	//Run the Push or Pull
	else if (PUSH_PULL){
		if (LOAD_BIT){
			if (HIGH_BIT){
				for (i = 0x8; i < RF_SIZE; i++){
					if (regListField(i - HALF_RF)){
						registers[i] = registerLoad(SP & 0x3FFF, memory);
						/* Post increment */
						alu = SP + REG_SIZE;
						SP = alu;
					}
				}
			}
			else{
				for (i = 0; i <= 0x7; i++){
					if (regListField(i)){
						registers[i] = registerLoad(SP & 0x3FFF, memory);
						alu = SP + REG_SIZE;
						SP = alu;
					}
				}
			}

			if (RET_BIT){

				PC = registerLoad(SP & 0x3FFF, memory);
				if (ir_flag != 0){
					ir_flag = 0;
				}
				alu = SP + REG_SIZE;
				SP = alu;
			}

		}
		/* PUSH */
		else{
			if (RET_BIT){
				SP = (0x3FFF & SP + ~REG_SIZE + 1) >> (unsigned)16;
				registerSave(SP & 0x3FFF, LR, memory);
			}
			if (HIGH_BIT){
				for (i = (RF_SIZE - 1); i >= 0x8; i--){
					if (regListField(i - HALF_RF)){
						alu = SP + ~REG_SIZE + 1;
						SP = alu;
						registerSave(SP & 0x3FFF, registers[i], memory);
					}
				}
			}
			else{
				for (i = 0x7; i >= 0; --i){
					if (regListField(i)){
						SP = SP + ~REG_SIZE + 1;
						registerSave(SP & 0x3FFF, registers[i], memory);
					}
				}
			}
		}
	}
	else if (BRANCH){
		if (LINK_BIT){
			LR = PC;
		}
		PC = OFF12;
		ir_flag = NOTSET;

	}
	//Stop Instrcution
	else if (0xE000){
		stop_flag = SET;
	}

}

/*************************************************************
*  checkBranch() - Check condition code and setALUFlag, if a branch
*                 is to be made, then return 1; else 0.
*
*
********************************************************/
int checkBranch(){
	if (EQ){
		if (zero_flag = SET){
			return 1;
		}
	}
	else if (NE){
		if (zero_flag == NOTSET){
			return 1;
		}
	}
	else if (CS){
		if (carry_flag == SET){
			return 1;
		}
	}
	else if (CC){
		if (carry_flag == NOTSET){
			return 1;
		}
	}
	else if (MI){
		if (sign_flag == SET){
			return 1;
		}
	}
	else if (PL){
		if (sign_flag == SET){
			return 1;
		}
	}
	else if (HI){
		if (carry_flag && zero_flag == NOTSET){
			return 1;
		}
	}
	else if (LS){
		if (carry_flag == NOTSET || zero_flag == SET){
			return 1;
		}
	}
	else if (AL){
		return 1;
	}

	return 0;
}


/*************************************************************************
* regListField() -
*			Checks for the current PUSH/PULL instruction if the register
*			file index passed to the PUSH/PULL.
********************************************************************/
int regListField(int index){
	switch (index){
	case 0:
		return LIST & 0x0;
	case 1:
		return LIST & 0x1;
	case 2:
		return LIST & 0x4;
	case 3:
		return LIST & 0x8;
	case 4:
		return LIST & 0x10;
	case 5:
		return LIST & 0x20;
	case 6:
		return LIST & 0x40;
	case 7:
		return LIST & 0x80;
	}
}

/****************************************************************
* setALUFlag()
* This checks for the flags and runs the sign flag bit shifts
*************************************************************/
void setALUFlag(uint32_t value){

	if (value == NOTSET)
		zero_flag = SET;
	else
		zero_flag = NOTSET;
	sign_flag = (value & 0x80000000) >> 31;
}

/****************************************************************
* CheckIfCarry
* Check if the carry bit is set
*************************************************************/
int checkIfCarry(uint32_t op1, uint32_t op2, uint8_t carryFlag){
	if ((op2 == MAX32) && (carryFlag == 1)) 
		return(1);
	return((op1 > (MAX32 - op2 - carryFlag)) ? 1 : 0);
}

/****************************************************************
* Modify Memory()
* Changes the current memory locations in the virtual memory
* this can change any value and read load it
*************************************************************/
void modify_memory(void * memory, unsigned int offset){
	unsigned char input[BUFFER_SIZE];
	unsigned int byte;
	unsigned int i;

	printf("Please Enter only HEX Bytes");

	while (1) {
		
		printf("%04X -- %02X >>> ", offset, *((unsigned char*)memory + offset));

		fgets(input, BUFFER_SIZE, stdin);
		
		input[2] = '\0';
	
		//Look for Exit
		if (input[0] == '.'){
			break;
		}
		// Check if input is null
		if (strcmp(input, "") == 0){
			continue;
		}
		if (strcmp(input, "\n") == 0){ continue;}

		for (i = 0; i < strlen(input); i++){
			input[i] = tolower(input[i]);
		}

		if (sscanf(input, "%x", &byte) == 0){
			continue;
		}

		*((unsigned char*)memory + offset) = byte;
		++offset;

		if (offset == MEMORY){
			printf("End of memory.\n");
			break;
		}
	}
}


