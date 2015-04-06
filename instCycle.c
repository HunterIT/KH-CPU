/**************************
 * Name: instCycle.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: March 30th, 2015
 *
 * Purpose: to run the instruction cycle for the go function
 */
 
#include "khcpu.h"

void instCycle(void * memory){
	
    if(f_ir == 0){
        fetch(memory);
        cir = IR0;
        execute(memory);
        f_ir = 1;
    }else{
        cir = IR1;
        execute(memory);
        f_ir = 0;
    }     

    return;
}
