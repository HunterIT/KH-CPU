/**************************
 * Name: KHCPU.h
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 * The header file for the KH-CPU virtual CPU
 */
 
 //C defined headers
 #include <stdio.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <ctype.h>
 #include <string.h>
 
 //User defined values
 #define MEMORY 0x4000			//The amount of accessable memory
 #define INPUT_SIZE 0x3			//User input size
 #define BUFFER_SIZE 0xFF		//Buffer size
 #define RF_SIZE	0x10
 #define REG_SIZE    0x4
 #define REG_SP     13
 #define REG_LR     14
 #define REG_PC     15
 #define RESET 		0
 #define BYTE_SIZE       ((int)sizeof(char))
 
 
//Regisiters and Flags
 static unsigned long regFile[RF_SIZE];
 static unsigned char f_sign, f_zero, f_carry, f_stop, f_ir;
 static unsigned long mbr, mar, ir;
 
//User defined function prototypes
void displayOptions (); 		 //Option Menu
void getInput(char *input); 	 //User Input Value
void userInput(); 				//User Selection
int LoadFile(void * memory, unsigned int max); //Load File
void WriteFile(void * memory); //Write File
void dump_memory( void *memory,unsigned int offset, unsigned int length );
void  modify_memory(void *memory, unsigned int offset);
int dump_reg();
void fetch(void *memory);
int reg_reset();

