/**************************
 * Name: execute.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: April 3rd, 2015
 *
 * Purpose: Finds the instruction cycle acknowledge instruction
 * 			fields, execute instruction based on instruction field values.
 */
 
#include "khcpu.h"
 
void execute(void *memory){
    unsigned int temp;
    unsigned int i;
    
    /* The current data procressing data for the OpCodes */
    
    if(DATA_PROC){
		/* Rd :=Rd AND Rn */
        if(AND){
            alu = regFile[RD] & regFile[RN];
            flags(alu);
            regFile[RD] = alu;
        /* Rd := Rd EOR Rn */
        }else if(EOR){
            alu = regFile[RD] ^ regFile[RN];
            flags(alu);
            regFile[RD] = alu;
        /* Rd := Rd - Rn */
        }else if(SUB){
            alu = regFile[RD] + ~regFile[RN] + 1;
            flags(alu);
            f_carry = iscarry(regFile[RD], ~regFile[RN], 1); //Check Carry
            regFile[RD] = alu;
        /* Rd := (signed)Rnbyte */
        }else if(SXB){
            alu = (signed)regFile[RN];
            flags(alu);
            regFile[RD] = alu;
        /* Rd := Rd + Rn */
        }else if(ADD){
            alu = regFile[RD] + regFile[RN];
            flags(alu);
            f_carry = iscarry(regFile[RD], ~regFile[RN], 0);
            regFile[RD] = alu;
         /* Rd := Rd + Rn + C */
        }else if(ADC){
            alu = regFile[RD] + regFile[RN] + f_carry; 
            flags(alu);
            f_carry = iscarry(regFile[RD], regFile[RN], f_carry);
            regFile[RD] = alu;  //Check for a Carry
        /* Rd := Rd >> Rn */
        }else if(LSR){
            alu = regFile[RD] >> regFile[RN];
            flags(alu);
            regFile[RD] = alu;   //Check for a Carry
        /* Rd := Rd << Rn */
        }else if(LSL){
            alu = regFile[RD] << regFile[RN];
            flags(alu);
            regFile[RD] = alu;  //Check for a Carry
        /* Rd AND Rn */
        }else if(TST){
            alu = regFile[RD] & regFile[RN];
            flags(alu);
        /* RD EOR Rn */
        }else if(TEQ){
            alu = regFile[RD] ^ regFile[RN];
            flags(alu);
        /* Rd - Rn */
        }else if(CMP){
            alu = regFile[RD] + ~regFile[RN] + 1;
            flags(alu);
            f_carry = iscarry(regFile[RD], ~regFile[RN], 1);
        /* Rd := Rd rotated right by Rn */
        }else if(ROR){
            for(i = 0; i < regFile[RN]; i++){
                
            }
        /* Rd := Rd OR Rn */
        }else if(ORR){
            alu = regFile[RD] | regFile[RN];
            flags(alu);
            regFile[RD] = alu;
        /* Rd :=  Rn */
        }else if(MOV){
            regFile[RD] = regFile[RN];
            flags(regFile[RD]);
        /* Rd := Rd AND NOT Rn (bit clear) */
        }else if(BIC){
            alu = regFile[RD] & !regFile[RN];
            flags(alu);
            regFile[RD] = alu;
        /* Rd := NOT Rn */
        }else if(MVN){
            alu = !regFile[RN];
            flags(alu);
            regFile[RD] = alu;
        }
    }

    else if(LOAD_STORE){
        
        //* load the register into the mar
        mar = regFile[RN];
        
        if(LOAD_BIT){
            printf("LOAD>>:  ");
            /*Load BIT */
            if(BYTE_BIT){
                printf("b\n");
                /*mbr <- mem[mar]*/
                mbr = *((unsigned char *)memory + mar);
                regFile[RD] = mbr;
            }
            /*Load Double Word*/
            else{
                printf("dw\n");
                for(i = 0; i < CYCLES; i++, mar++){
                    mbr = mbr << SHIFT_BYTE;
                    mbr += *((unsigned char*)memory + mar);
                }
                regFile[RD] = mbr;
            }
        }else{
            /*Store Byte*/
            if(BYTE_BIT){
                mbr = regFile[RD];
                *((unsigned char*)memory + mar) = (unsigned char)mbr & BYTE_MASK;
            }
            /*Store Double Word*/
            else{
                mbr = regFile[RD];
                *((unsigned char*)memory + mar++) = (unsigned char)(mbr >> SHIFT_3BYTE & BYTE_MASK);
                *((unsigned char*)memory + mar++) = (unsigned char)(mbr >> SHIFT_2BYTE & BYTE_MASK);
                *((unsigned char*)memory + mar++) = (unsigned char)(mbr >> SHIFT_BYTE & BYTE_MASK);
                *((unsigned char*)memory + mar) = (unsigned char)mbr & BYTE_MASK;
            }
        } 
    /* 
     * Immediate Operations 
     */
    }else if(IMMEDIATE){
        /* IM_MOVe immediate value into regFile at RD */
        if(IM_MOV){
            regFile[RD] = IMM_VALUE;    
            flags(regFile[RD]);
        }else if(IM_CMP){
            alu = ~(regFile[RD] + IMM_VALUE) + 1;
            flags(alu);
            f_carry = iscarry(regFile[RD], ~IMM_VALUE, 0);
        }else if(IM_ADD){
            alu = regFile[RD] + IMM_VALUE;
            flags(alu);
            f_carry = iscarry(regFile[RD], IMM_VALUE, 0);
            regFile[RD] = alu;
        }else if(IM_SUB){
            alu = regFile[RD] + ~IMM_VALUE + 1;
            flags(alu);
            f_carry = iscarry(regFile[RD], ~IMM_VALUE, 1);
            regFile[RD] = alu;
        }    
        
    }else if(COND_BRANCH){
        /* Check condition codes and flags */
        if(dpu_chkbra()){
            /* Add relative address as a signed 8-bit */
            alu = PC + (int8_t)COND_ADDR;
            PC = alu;
        }
    //PUSH PULL 
    }else if(PUSH_PULL){
    }
    
    //BRANCH IT
    else if(BRANCH){
        if(LINK_BIT){
            LR = PC;
        }    
        PC = OFFSET12;

	//STOP IT
    }else if(STOP){
        f_stop = 1;
    }    
    
    return;
}    

