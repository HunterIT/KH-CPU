/**************************
 * Name: dumpMemoryMod.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 */

#include "khcpu.h"

void MemDump(void *memory, unsigned int offset, unsigned int length)
{
	unsigned int i, j;  	//keep track of the inner for loop 
	unsigned int row = 0x10;   //The max a row can be
	length--;
	
	/** 
	 * The following inner for loop prints out the all the 
	 * HEX values of the loop by reading all the memory componets
	 * of the loaded file into the memory address
	 */ 
	
	for (i = offset; i < (offset + length); i += row) {
		
		//Prints out a the HEX values here
		printf("%4X\t", i);
	
		/** every row that is here, it will print out column if it
		 * is greater then row length
		 */ 
		for(j = i; j < (i + row); j++) {
			
			printf("%2X ", *((char *) memory + j));
			
			//Break if it's over the length of the row
			if(j == (offset + length)) break;
		} 
		
		//Break to a new line 
		printf("\n\t");


		/** 
		* The next row below is used to print out the "actual" values of the
		* loaded file. For a text file, here is where it is display the actual
		* human readable content here. 
		*/ 
		for(j = i; j < (i + row); j++) {
			if(isprint((int) *((char *) memory + j)))
				printf(" %c ", *((char *) memory + j));
			else
				printf(" . ");
				
			if(j == (offset + length)) break;
		}
		
		printf("\n");
		
		if(j == length) break;
	}
return;
}		

void modify_memory(void *memory, unsigned int offset)
{
    char user_input;
    printf("End the Memory Mod by '.'");
    
    //Loop untill required by the user to stop
    while(1) {
		
		//Display current offset
        fprintf(stdout, "%4X> ", offset);
        
        while(getchar() != '\n');
       
		//Break if user has terminated it
        if((user_input = getchar()) == '.')
            break;
            
         //Change the memory location
        *((char *) memory + offset) = user_input;
        
        if(++offset == MEMORY)
            break;
    }
    
    return;
}
