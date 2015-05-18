/**************************
* Name: khcpu.h
* Author: Kenneth Hunter
* URL: http://www.hunterit.ca
* Email: kenneth@hunterit.ca
* Course: Computer Architecture
* Last Revision: May, 5th, 2015
*
* Purpose: This is a header file for my KHCPU.c
***************************/

/*C Headers used. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>


/*Function Prototypes*/
void reset();
void intro();
void displayOptions();
void userInterface();
void writeFile(void * memory);
int loadFile(void * memory, unsigned int max);
void dump_memory(void * memory, unsigned int offset, unsigned int length);
void modify_memory(void * memory, unsigned int offset);
int dump_reg();
void fetch(void * memory);
void help();
void execute(void * memory);
void runCycle(void * memory);
void setALUFlag(uint32_t value);
int checkIfCarry(uint32_t op1, uint32_t op2, uint8_t carry_flag);
int checkBranch();
void registerSave(uint32_t new_mar, uint32_t new_mbr, void * memory);
uint32_t registerLoad(uint32_t new_mar, void * memory);
int regListField(int index);


/*Speical Values*/
#define MEMORY 		0x4000	
#define BUFFER_SIZE 0x100
#define SET			1
#define NOTSET		0
#define MSBTOLSB    31

/* Registers */
static uint32_t registers[0x10];
#define SP registers[0xD]
#define LR registers[0xE]
#define PC registers[0xF]
#define IR0 (unsigned)ir >> 16
#define IR1 ir & 0FFFF
static uint32_t mar;
static uint32_t mbr;
static uint32_t ir;
static uint32_t alu;
static uint32_t currentI;  //Temp Reg

/*Flag */
static uint8_t sign_flag;
static uint8_t carry_flag;
static uint8_t zero_flag;
static uint8_t stop_flag;
static uint8_t ir_flag;

/* Special Registers in Register File Offsets */
#define RF_SP   0xD
#define RF_LR   0xE
#define RF_PC   0xF
#define SP      registers[RF_SP]
#define LR      registers[RF_LR]
#define PC      registers[RF_PC]
#define LIST    currentI & 0xFF

//User defined values
#define MAX32  		0xFFFFFFFF	//Max memory for 32 bit
#define MEMORY 		0x4000		//The amount of accessable memory
#define INPUT_SIZE	0x3			//User input size
#define BUFFER_SIZE 0x100		//Buffer size
#define RF_SIZE		0x10
#define REG_SIZE	0x4			//Register Size
#define REG_SP		0xD			//Stack Pointer	Register Number	
#define REG_LR		0xE			//Link Register Number
#define REG_PC		0xF			//Program Counter Register
#define RESET 		0			//Used for Reset Flags
#define BYTE_SIZE	0x1			//Declare the size of byte

//Instructions
#define form (unsigned)currentI >> 13		//Declare pointer location
#define PROC form == 0x0					//Test if a data process, delcare different data types
#define LOAD_STORE form == 0x1
#define IMMEDIATE form == 0x2 | form == 0x3
#define COND_BRANCH form == 0x4
#define PUSH_PULL form == 0x5
#define BRANCH form == 0x6
#define STOP currentI == 0xE000

/* Instruction Registers */
#define IR0 (unsigned)ir >> 16	
#define IR1 ir & 0xFFFF

/* Misc Values for header/cpu*/
#define HALF_RF     RF_SIZE/2
#define IMM_VALUE	((currentI >> 4) & 0xFF)	
#define COND_ADDR	currentI & 0xFF
#define RET_BIT     ((currentI >> 8) & 0x1)
#define LOAD_BIT	((currentI >> 11) & 0x1)
#define BYTE_BIT	((currentI >> 10) & 0x1)
#define HIGH_LOW	((currentI >> 10) & 0x1)
#define HIGH_BIT	((currentI >> 10) & 0x1)
#define R			((currentI >> 8) & 0x1)
#define REG			 currentI & 0xFF
#define LINK_BIT	((currentI >> 12) & 0x1)
#define OFF12		currentI & 0xFF
#define OPERATION	((currentI >> 8) & 0xF)
#define RN			((currentI >> 4) & 0xF)
#define RD			currentI & 0xF

/* Declare the OPCODES for DATA PROCESSING */
#define PROCESSING ((currentI >> 8) & 0xF)
#define AND 0x0 == PROCESSING
#define EOR 0x1 == PROCESSING
#define SUB 0x2 == PROCESSING
#define SXB 0x3 == PROCESSING
#define ADD 0x4 == PROCESSING
#define ADC 0x5 == PROCESSING
#define LSR 0x6 == PROCESSING
#define LSL 0x7 == PROCESSING
#define TST 0x8 == PROCESSING
#define TEQ 0x9 == PROCESSING
#define CMP 0xA == PROCESSING
#define ROR 0xB == PROCESSING
#define ORR 0xC == PROCESSING
#define MOV 0xD == PROCESSING
#define BIC 0xE == PROCESSING
#define MVN 0xF == PROCESSING

/* Immediate OpCodes */
#define MOVEOPCODE ((currentI >> 12) & 0x3)
#define IMM_MOV 0x0 == MOVEOPCODE
#define IMM_CMP 0x1 == MOVEOPCODE
#define IMM_ADD 0x2 == MOVEOPCODE
#define IMM_SUB 0x3 == MOVEOPCODE

/* Branch Condition Codes */
#define MOVEBRANCH ((currentI >> 8) & 0xF)
#define EQ 0x0 == MOVEBRANCH
#define NE 0x1 == MOVEBRANCH
#define CS 0x2 == MOVEBRANCH
#define CC 0x3 == MOVEBRANCH
#define MI 0x4 == MOVEBRANCH
#define PL 0x5 == MOVEBRANCH
#define HI 0x8 == MOVEBRANCH
#define LS 0x9 == MOVEBRANCH
#define AL 0xE == MOVEBRANCH
