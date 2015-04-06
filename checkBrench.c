/**************************
 * Name: checkBranch.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: April 1st, 2015
 *
 * Purpose: The following function is to check the branch instructions
 *
 */
 
#include "khcpu.h"

int checkBranch(){
    if(EQ){
        if(f_zero) return 1; 
    }else if(NE){ 
		if(!f_zero) return 1;
    }else if(CS){
		if(f_carry) return 1;
    }else if(CC){
        if(!f_carry) return 1;
    }else if(MI){
		if(f_sign) return 1;      
    }else if(PL){
        if(!f_sign) return 1;
    }else if(HI){
        if(f_carry && !f_zero) return 1;   
    }else if(LS){
        if(!f_carry || f_zero) return 1;
    }else if(AL){
		return 1;
    }
    return 0;
}
