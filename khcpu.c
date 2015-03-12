/**************************
 * Name: KH-CPU.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 * Purpose: The following program is a virtual CPU based on 16k of memory. 
 * 			The purpose of this lab is to create the basic software to run
 *          and control on a virtual realtime CPU. The software has 
 *          the functions that include
 *  		  - Dump Memory
 *            - Go (Run the entrie loaded program
 *            - Load a file into memory
 *            - Modifity Memory
 *            - Display current regisiters
 *            - Trace mode
 *            - Write to a file in memory
 *            - Reset the registers to zero postion
 */
#include "khcpu.h"

int main (void) {

    displayOptions(); 
    userInput();
    return 0;
} 

/**
 * displayOptions
 * 
 * Displays a list of options to the user
 */
void displayOptions () {
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
 

/**
 * userInput()
 * 
 * Ask the user what its input is, then
 * capture the input and run the function
 */
void userInput() {

    char input;
    int file_result;
    char mem[MEMORY];
    unsigned int offset, row_length; /* for user input */


    while (1) {

    printf("\n$> ");
    fgets(&input, 3, stdin);
   
    switch (input) {
        case 'D':
        case 'd': printf("Select an Offset> ");
				  fscanf(stdin, "%X", &offset);
				  printf("Select a length> ");
				  fscanf(stdin, "%X", &row_length);
				  MemDump((void *) mem, offset, row_length);
				  getchar();
                  break;
        case 'G':
        case 'g': printf("Go function has not been implemented yet!");
                  //go();
                  break;
        case 'L':
        case 'l': if((file_result = LoadFile(mem, MEMORY)) > 0) 
                      printf("The Loaded file has %d bytes that were read", file_result);
                  else printf("The file has failed to load");
                  break;
        case 'M':
        case 'm': printf("Select an Offset> ");
                  fscanf(stdin, "%X", &offset);
                
                  modify_memory(mem, offset);
                  getchar();
                  break;
        case 'Q':
        case 'q': printf("Goodbye!\n");
                  exit(0);
                  break;
        case 'R':
        case 'r': dump_reg();
                  break;
        case 'T':
        case 't': fetch(mem);
				  dump_reg();
                  break;
        case 'W':
        case 'w': WriteFile(mem);
                  break;
        case 'Z':
        case 'z': reg_reset();
                  break;
        case '?':
        case 'H':
        case 'h': displayOptions();
                  break;
        default: printf("Nothing selected");
    }
    } 
} 


