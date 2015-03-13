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
	
    unsigned int i;
    unsigned int j = REG_SIZE;
    
    //PC to MAR
    mar = regFile[REG_PC];
    
    printf("MAR = %lu", mar);
    printf("SIZE = %d", j);
    
    //Memory[MAR to MBR
    for(i = 0; i < j; i++){
        mbr = mbr << 8;
        mbr += *((unsigned char*)memory + (mar + i));
    }    
    
    ir = mbr;
    regFile[REG_PC] += REG_SIZE;
}
