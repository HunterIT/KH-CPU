/**************************
 * Name: flagscarry.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 * Purpose: Is to set the zero flag and to check if it's carry
 *
 */
 
#include "khcpu.h"
       
void flags(uint32_t alu){        
    if(alu == 0){
        f_zero = 1;
    }else{
        f_zero = 0;
    }    
    f_sign = alu & MSB32_MASK;
    return;
}

int iscarry(uint32_t op1,uint32_t op2, uint8_t c){
    if ((op2== MAX32)&&(c==1)) return(1); 
    return((op1 > (MAX32 - op2 - c))?1:0);
}
