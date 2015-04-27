/**************************
* Name: khcpu.h
* Author: Kenneth Hunter
* URL: http://www.hunterit.ca
* Email: kenneth@hunterit.ca
* Course: Computer Architecture
* Last Revision: April, 26th, 2015
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
int checkIfCarry(uint32_t op1, uint32_t op2, uint8_t c);
int checkBranch();
void registerSave(uint32_t new_mar, uint32_t new_mbr, void * memory);
uint32_t registerLoad(uint32_t new_mar, void * memory);
int regListField(int index);


/*Speical Values*/
#define MEMORY 	0x4000	
#define BUFFER_SIZE 0x100
#define SET 1
#define NOTSET 0
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
static uint32_t currentI;

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
#define CYCLES  (REG_SIZE / BYTE_SIZE)
#define LIST    currentI & 0xFF

//User defined values
#define MAX32  	0xFFFFFFFF  //Max memory for 32 bit
#define MEMORY 	0x4000		//The amount of accessable memory
#define INPUT_SIZE 0x3			//User input size
#define BUFFER_SIZE 0x100		//Buffer size
#define RF_SIZE	0x10	
#define REG_SIZE   0x4			//Register Size
#define REG_SP     0xD			//Stack Pointer			
#define REG_LR     0xE			//
#define REG_PC     0xF			//Program Counter Register
#define RESET 		0
#define BYTE_SIZE  0x1

//Instructions
#define PROC (unsigned)currentI >> 13 & 0x0
#define LOAD_STORE (unsigned)currentI >> 13 & 0x1
#define IMMEDIATE (unsigned)currentI >> 13 & 0x2 | 0x3
#define COND_BRANCH (unsigned)currentI >> 13 & 0x4
#define PUSH_PULL (unsigned)currentI >> 13 & 0x5
#define BRANCH (unsigned)currentI >> 13 & 0x6
#define STOP 0xE000

/* Instruction Registers */
#define IR0 (unsigned)ir >> 16 
#define IR1 ir & 0xFFFF
#define HALF_RF     RF_SIZE/2
#define IMM_VALUE ((currentI >> 4) & 0xFF)
#define CONDITION ((currentI >> 8) & 0xF)
#define COND_ADDR currentI & 0xFF
#define RET_BIT     ((currentI >> 8) & 0x1)
#define LOAD_BIT ((currentI >> 11) & 0x1)
#define BYTE_BIT ((currentI >> 10) & 0x1)
#define HIGH_LOW ((currentI >> 10) & 0x1)
#define HIGH_BIT ((currentI >> 10) & 0x1)
#define R		 ((currentI >> 8) & 0x1)
#define REG		  currentI & 0xFF
#define LINK_BIT ((currentI >> 12) & 0x1)
#define OFF12  currentI & 0xFF
#define OPERATION ((currentI >> 8) & 0xF)
#define RN         ((currentI >> 4) & 0xF)
#define RD         currentI & 0xF

/* Declare the OPCODES for DATA PROCESSING */
#define AND 0x0 == ((currentI >> 8) & 0xF)
#define EOR 0x1 == ((currentI >> 8) & 0xF)
#define SUB 0x2 == ((currentI >> 8) & 0xF)
#define SXB 0x3 == ((currentI >> 8) & 0xF)
#define ADD 0x4 == ((currentI >> 8) & 0xF)
#define ADC 0x5 == ((currentI >> 8) & 0xF)
#define LSR 0x6 == ((currentI >> 8) & 0xF)
#define LSL 0x7 == ((currentI >> 8) & 0xF)
#define TST 0x8 == ((currentI >> 8) & 0xF)
#define TEQ 0x9 == ((currentI >> 8) & 0xF)
#define CMP 0xA == ((currentI >> 8) & 0xF)
#define ROR 0xB == ((currentI >> 8) & 0xF)
#define ORR 0xC == ((currentI >> 8) & 0xF)
#define MOV 0xD == ((currentI >> 8) & 0xF)
#define BIC 0xE == ((currentI >> 8) & 0xF)
#define MVN 0xF == ((currentI >> 8) & 0xF)

/* Immediate OpCodes */
#define MOV 0x0 == ((currentI >> 12) & 0x3)
#define CMP 0x1 == ((currentI >> 12) & 0x3)
#define ADD 0x2 == ((currentI >> 12) & 0x3)
#define SUB 0x3 == ((currentI >> 12) & 0x3)

/* Branch Condition Codes */
#define EQ 0x0 == ((currentI >> 8) & 0xF)
#define NE 0x1 == ((currentI >> 8) & 0xF)
#define CS 0x2 == ((currentI >> 8) & 0xF)
#define CC 0x3 == ((currentI >> 8) & 0xF)
#define MI 0x4 == ((currentI >> 8) & 0xF)
#define PL 0x5 == ((currentI >> 8) & 0xF)
#define HI 0x8 == ((currentI >> 8) & 0xF)
#define LS 0x9 == ((currentI >> 8) & 0xF)
#define AL 0xE == ((currentI >> 8) & 0xF)
