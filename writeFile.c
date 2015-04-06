/**************************
 * Name: writeFile.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: February 25th, 2015
 *
 * Purpose: The following function is to write in a file for the 
 *          different options of the CPU
 *
 */
 
 #include "khcpu.h"

void WriteFile(void * mem) {

    FILE *f;  //The File
    char flushInput[3]; //Flush the input 
    char name[BUFFER_SIZE];
    int num_bytes; //Number of Bytes
    int write_bytes; //Bytes that have been written

    //Ask the User for file name
    printf("\nEnter a File Name:");
    fgets(name, BUFFER_SIZE, stdin);

    //Make last byte NULL
    name[strlen(name) -1] = '\0';

    //Ask the user the number of bytes to write
    printf("\nHow much bytes do you want to write?");
    scanf("%d", &num_bytes);
    fgets(flushInput, 3, stdin);

    //Open the File
    if ((f = fopen(name, "wb")) == NULL) {
        printf("\nFailed to open the file");
    }

    if ((write_bytes = fwrite(mem, 1, num_bytes, f)) < 0) {
        printf("Error: Could not write to file");
    } else { 
        printf("There has been %d bytes that have been written\n", write_bytes);
    } 

    return;
} 
