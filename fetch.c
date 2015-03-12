/**************************
 * Name: fetch.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 * Purpose: The following function fetchs the current registers sets
 *           and is used in the trace command to scan though every set
 *
 */
 
#include "khcpu.h"

void fetch(void * memory){
	
    unsigned int i, cycles;
   
    cycles = REG_SIZE / ((int)sizeof(char));

    //PC to MAR
    mar = regFile[REG_PC];
    
    
    //Memory[MAR to MBR
    for(i = 0; i < cycles; i++){
        mbr = mbr << 8;
        //Adding the memory at mar location to mbr
        mbr += *((unsigned char*)memory + (mar + i));
    }    
    //MBR to IR
    ir = mbr;
    
    //Incrase the PC by 1
    regFile[REG_PC] += REG_SIZE;
}
