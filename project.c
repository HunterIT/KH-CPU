/**************************
 * Name: project.c
 * Author: Kenneth Hunter
 * URL: http://www.hunterit.ca
 * Email: kenneth@hunterit.ca
 * Course: Computer Architecture
 * Last Revision: January 30th, 2015
 *
 * Purpose: This is a beginning of our major project
 *          the following program will display a list
 *          of commands that the user can use select
 */
#include <stdio.h>
#define MEM_SIZE 16384
#define BUFFER_SIZE 256

void displayOptions (); //Declare the Option Menu
void getInput(char *input); //Get the Input from the User
void userInput(); //User Selection
int LoadFile(void * memory, unsigned int max); //Load File
void WriteFile(void * memory); //Write File

int main (void) {

    displayOptions(); 
    userInput();
    return 0;
} 

/**
 * displayOptions
 * 
 * Displays a list of options to the user
 */
void displayOptions () {
    printf("Please select an option!\n\n");
    printf("d\t\t--Dump memory\n");
    printf("g\t\t--Go - run the entire program\n");
    printf("l\t\t--Load a file into memory\n");
    printf("m\t\t--Memory modify\n");
    printf("q\t\t--Quit program\n");
    printf("r\t\t--Display registers\n");
    printf("t\t\t--Trace - execute one instruction\n");
    printf("w\t\t--Write file\n");
    printf("z\t\t--Reset all registers to zero\n");
    printf("?, h\t\t--Display list of commands\n");
}
 

/**
 * userInput()
 * 
 * Ask the user what its input is, then
 * capture the input and run the function
 */
void userInput() {

    char input;
    int file_result;
    char mem[MEM_SIZE];


    while (1) {

    printf("\n$> ");
    fgets(&input, 3, stdin);
   
    switch (input) {
        case 'D':
        case 'd': printf("Dump memory has not been implemented yet!");
                  //dumpMemory();
                  break;
        case 'G':
        case 'g': printf("Go function has not been implemented yet!");
                  //go();
                  break;
        case 'L':
        case 'l': if((file_result = LoadFile(mem, MEM_SIZE)) > 0) 
                      printf("The Loaded file has %d bytes that were read", file_result);
                  else printf("The file has failed to load");
                  break;
        case 'M':
        case 'm': printf("Memory modify has not been implemented yet!");
                  //MemoryModify();
                  break;
        case 'Q':
        case 'q': printf("Goodbye!\n");
                  exit(0);
                  break;
        case 'R':
        case 'r': printf("Display registers has not been implemented yet!");
                  //DisplayRegisters();
                  break;
        case 'T':
        case 't': printf("Trace function has not been implemented yet!");
                  //trace();
                  break;
        case 'W':
        case 'w': WriteFile(mem);
                  break;
        case 'Z':
        case 'z': printf("Reset function has not been implemented yet!");
                  //Reset();
                  break;
        case '?':
        case 'H':
        case 'h': displayOptions();
                  break;
        default: printf("Nothing selected");
    }
    } 
} 

/**
 * int LoadFile()
 * 
 * Loads a file in the memory
 */
int LoadFile(void * memory, unsigned int max) {
    
    FILE *f;        //The File loaded
    int size;  //The file size
    char name[BUFFER_SIZE]; //The name given by USER

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

    fclose(f);
    return size; 
} 

/**
 * WriteFile
 * 
 * Wirte a file to the file
 */
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

void memDump(void *memptr, unsigned offset, unsigned length)
{
	
 

    
