/**************************
 * Name: modify_memory.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 * Purpose: To mod the current HEX values in the memory
 */
 
#include "khcpu.h"

void modify_memory(void *memory, unsigned int offset)
{
    unsigned int byte;
    unsigned int i;
    unsigned char user_input[BUFFER_SIZE];
    unsigned char flush[BUFFER_SIZE];
    
    printf("End the Memory Mod by '.'\nS = Offset, V = Current Value!!\n\n");
    

    for(;;){
        // Display Current Offset & Value
        printf("S = %4.4X || V = %2.2X > ", offset, *((unsigned char*)memory + offset));
        
        // Get the User Input
        fgets(user_input, BUFFER_SIZE, stdin);
        
        // Create a New Line
        user_input[2] ='\0';

        // Check if the user has quit
        if(user_input[0] == '.'){
            break;    
        }
        // Check Input if Null or Null Terminating 
        if(strcmp(user_input, "") == 0 || strcmp(user_input, "\n") == 0 ){
            continue;
		}

        // Capture HEX Byte.
        if(sscanf(user_input, "%x", &byte) == 0){
            continue;
        }

        // Assign offset with new byte value
        *((unsigned char*)memory + offset) = byte;
        
        
        //Add the offset by 1
        offset++;
        
        if(offset == MEMORY) { printf("No Memory Found.");
            break;
        }    
    }
}
