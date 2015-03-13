/**************************
 * Name: dumpMemory.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 */

#include "khcpu.h"

void dump_memory(void * memory, unsigned int offset, unsigned int length){
    unsigned int i;
    unsigned int lineLength = 0x10;
    unsigned char line[0x10];
    unsigned int count = 0;

    while(count < length){
    
        if(offset == MEMORY){
            break;
        } 

        //Print the Offset & Block Number
        printf("%4.4X\t", offset);
        
       
        // Create the line of the HEX Digits
        for(i = 0; i < 0x10; i++, offset++, count++){
			
			//*CHECKS* to see if the pointer is not going out of bounds
            if(offset == MEMORY){
                lineLength = i;
                break;
            }
            
            //*CHECKS* to see if it's staying the limited length
            if(count == length){
                lineLength = i;
                break;
            }      
            
            line[i] = *((char*)memory + offset);
            printf("%2.2X ", line[i]);
        }
        printf("\n\t");
        
        
        //Next Line, PRINT OUT ASCII VALUES
        for(i = 0; i < lineLength; i++){
            if(isprint(line[i])){
                printf(" %c ", line[i]);  //Prints out ASCII if valid
            }else{
                printf(" . ");		//Prints out DOT if not valid
            }    
        }
        //Do it Again.... 
        printf("\n");
    }
}
