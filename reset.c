/**************************
 * Name: reset.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: March 6th, 2015
 *
 * Purpose: the following function is to reset the registers
 */
 
#include "khcpu.h"


int reg_reset(){
	unsigned int i;
	
	for(i = 0; i < RF_SIZE; i++){
		regFile[i] = RESET;
	}
	// Reset flags
	f_sign = RESET;
	f_zero = RESET;
	f_carry = RESET;
	f_stop = RESET;
	f_ir = RESET;
	// Non-visible registers
	mar = RESET;
	mbr = RESET;
	ir = RESET;
return 0;
}


