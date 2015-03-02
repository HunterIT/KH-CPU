/**************************
 * Name: loadFile.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 * Purpose: The following function is to load in a file for the 
 *          different options of the CPU to write/read or modify
 *
 */
 
#include "khcpu.h"

/**
 * int LoadFile()
 * 
 * Loads a file in the memory
 */
int LoadFile(void * memory, unsigned int max) {
    
    FILE *f;       
    int size;  					//The file size
    char name[BUFFER_SIZE]; 	//Get the name of the file

    //Ask the user for the File Name/Type
    printf("File Name: ");
    fgets(name, BUFFER_SIZE, stdin);

    //Remove the last byte to NULL
    name[strlen(name) - 1] = '\0';

    //Test if you can open the file
    if((f = fopen(name, "rb")) == NULL) {
        return -1;
    }

	fseek(f, 0, SEEK_END);

    size = ftell(f);

    //Test to see if the file is truncated        
    if (size > max) {
        printf("The selected file has been truncated\n");
        size = max;
        }

    rewind(f);
    
    return fread(memory, sizeof(char), size, f);
} 
