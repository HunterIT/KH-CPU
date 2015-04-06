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
 #include <stdint.h>
 
 //User defined values
 #define MAX32  	0xFFFFFFFF  //Max memory for 32 bit
 #define MEMORY 	0x4000		//The amount of accessable memory
 #define INPUT_SIZE 0x3			//User input size
 #define BUFFER_SIZE 0xFF		//Buffer size
 #define RF_SIZE	0x10	
 #define REG_SIZE   0x4
 #define REG_SP     13			
 #define REG_LR     14			
 #define REG_PC     15			//Program Counter Register
 #define RESET 		0
 #define BYTE_SIZE ((int)sizeof(char))
 
 /* Registers */
static uint32_t  regFile[RF_SIZE];
static uint32_t  mar;
static uint32_t  mbr;
static uint32_t  ir;
static uint32_t  alu;
static uint16_t  cir;

/* Flags */
static uint8_t f_sign;
static uint8_t f_zero;
static uint8_t f_carry;
static uint8_t f_stop;
static uint8_t f_ir;
 
 /* Special Registers in Register File Offsets */
#define RF_SP   0xD
#define RF_LR   0xE
#define RF_PC   0xF
#define SP      regFile[RF_SP]
#define LR      regFile[RF_LR]
#define PC      regFile[RF_PC]
#define CYCLES  (REG_SIZE / BYTE_SIZE)
#define SHIFT_3BYTE 24
#define SHIFT_2BYTE 16
#define SHIFT_BYTE  8
#define MSB32_MASK  0x80000000
#define MSB_BYTE    0x80
#define BYTE_MASK   0xFF
 
//Instructions
#define DATA_PROC (unsigned)cir >> 13 & 0x0
#define LOAD_STORE (unsigned)cir >> 13 & 0x1
#define IMMEDIATE (unsigned)cir >> 13 & 0x2 | 0x3
#define COND_BRANCH (unsigned)cir >> 13 & 0x4
#define PUSH_PULL (unsigned)cir >> 13 & 0x5
#define BRANCH (unsigned)cir >> 13 & 0x6
#define STOP 0xE000

/* Instruction Registers */
#define IR0 (unsigned)ir >> 16 
#define IR1 ir & 0xFFFF
 
/* Instruction Fields */
#define LOAD_BIT ((cir >> 11) & 0x1)
#define BYTE_BIT ((cir >> 10) & 0x1)
#define HIGH_LOW ((cir >> 10) & 0x1)
#define R ((cir >> 8) & 0x1)
#define REG_LIST cir & 0xFF
#define LINK_BIT ((cir >> 12) & 0x1)
#define OFFSET12 cir & 0xFF
#define OPERATION ((cir >> 8) & 0xF)
#define RN ((cir >> 4) & 0xF)
#define RD cir & 0xF
#define OPCODE ((cir >> 12) & 0x3)
#define IMM_VALUE ((cir >> 4) & 0xFF)
#define CONDITION ((cir >> 8) & 0xF)
#define COND_ADDR cir & 0xFF

/* Declare the OPCODES for DATA PROCESSING */
#define AND 0x0 & OPERATION
#define EOR 0x1 & OPERATION
#define SUB 0x2 & OPERATION
#define SXB 0x3 & OPERATION
#define ADD 0x4 & OPERATION
#define ADC 0x5 & OPERATION
#define LSR 0x6 & OPERATION
#define LSL 0x7 & OPERATION
#define TST 0x8 & OPERATION
#define TEQ 0x9 & OPERATION
#define CMP 0xA & OPERATION
#define ROR 0xB & OPERATION
#define ORR 0xC & OPERATION
#define MOV 0xD & OPERATION
#define BIC 0xE & OPERATION
#define MVN 0xF & OPERATION

/* Immediate OpCodes */
#define IM_MOV 0x0 & OPCODE
#define IM_CMP 0x1 & OPCODE
#define IM_ADD 0x2 & OPCODE
#define IM_SUB 0x3 & OPCODE

/* Branch Condition Codes */
#define EQ 0x0 & CONDITION
#define NE 0x1 & CONDITION
#define CS 0x2 & CONDITION
#define CC 0x3 & CONDITION
#define MI 0x4 & CONDITION
#define PL 0x5 & CONDITION
#define HI 0x8 & CONDITION
#define LS 0x9 & CONDITION
#define AL 0xE & CONDITION
/* Forever loop */
#define forever for(;;)

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
void help();
void execute(void * memory);
void instCycle(void * memory);
void flags(uint32_t alu);
int iscarry(uint32_t op1, uint32_t op2, uint8_t c);


