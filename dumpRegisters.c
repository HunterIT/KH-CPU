/**************************
 * Name: dumpRegisters.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: March 6th, 2015
 *
 * Purpose: to dump all the current registers to the display
 */
 
#include "khcpu.h"


int dump_reg(){
	
    unsigned short ir0, ir1;
    unsigned int i;

    /* Print regsiter file */
    for(i = 0; i < RF_SIZE; i ++){
        if(i % 6 == 0){
            printf("\n");
        }
        
    switch(i) {
		case REG_SP: 
				printf(" SP:%8.8X ", regFile[REG_SP]);
				break;
		case REG_LR: 
				printf(" LR:%8.8X ",  regFile[REG_LR]);
				break;
		case REG_PC:
				printf(" PC:%8.8X ",  regFile[REG_PC]);
				break;
		default:
				printf("r%2.2d:%8.8X ", i,  regFile[i]);
				break;
		} 
	}

    printf("\t SZC:%c%c%c", f_sign, f_zero, f_carry);
    
    ir0 = ir >> 16;
    ir1 = ir & 0x0000FFFF;
      
    printf("\n	MAR:%8.8X", mar);
    printf("\t	MBR:%8.8X", mbr);
    printf("\t  IR0:%4.4X", ir0);
    printf("\t  IR1:%4.4X", ir1);
    printf("\t  Stop:%c ", f_stop);
    printf("\t  IR Flag:%c\n", f_ir);
  
    return 0;
}



