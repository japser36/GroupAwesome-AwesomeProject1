#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/** 
 * Handling of all the imports of file IO functions, @param {int} n and m for the later bitwise operations
 * Implicit declaration of the handleAddress function before the main method to allow the usage within the main function 
 * 
 */
FILE *rkt;
int n, m; 

int handleAddress(int n, int m, unsigned int v);

int main(int argc, char *argv[]){
    /**
     * Declaring @param for file path that user can dictate where the binary address file is located
     * Filedata will be the int value read from file for bitwise operations
     */
    char filePath[255];
    int fileData;
    int bitmask = ~((~0) << 16);

    // Getting user input for the file path to read into bitwise processor
    printf("Enter the address of the input file: ");
    // using a string format input via scanf
    scanf("%s", filePath);

    // verify the input, by printing the filepath back to the user
    printf( "\nYou entered: ");
    puts(filePath);

    // File open attempt and varification of file opened below
    rkt = fopen(filePath,"r");
    // If the file is not opened, return an error for the user to correct their mistake
    // else continue and let user know that the operation has begun 
    if (rkt == NULL) {
        printf("\nError while loading the file\n");
        exit(1);
    } else {
        printf("\nFile read successfully, beginning read and addressing operations\n");
    }

    // this prints the first line of the test file
    // read the line in strings
    fscanf(rkt,"%d", &fileData);
    // Setting the value n for later bitwise operation here
    n = ((int) (fileData)) & bitmask;
    // prints the file data in the output
    printf("\nValue of the n value is %d \n", n);


    // this prints the second line of the test file
    // read the line in strings
    fscanf(rkt,"%d", &fileData);
    // Setting the value n for later bitwise operation here
    m = ((int) (fileData)) & bitmask;
    // prints the file data in the output
    printf("Value of the m value is %d\n", m); 

    /**
     * Switched the break condition to EOF as per fscanf design instead of using the previous
     * fscanf(rkt, "%s ", fileData)!= 1 which seemed to cause issues in the sustem
     * Idea for eof was inspired by this: 
     * https://stackoverflow.com/questions/1835986/how-to-use-eof-to-run-through-a-text-file-in-c
     *
     */
    do {
        /**
         * Once the @param (int) n and @param (int) m are declared in the previous two lines of read 
         * We can now start iterating through the addresses and return the results of these addresses at once
         * Hence, implicit declaration of the function handleAddress above main function allows us to call it right now 
         * For each address in the file, we will send it through the handleAddress
         * This code has been shortened with the use of a do..while loop
         */
        fscanf(rkt, "%d", &fileData);
        handleAddress(n,m, fileData & bitmask);
    } while (!feof(rkt));

    // close the file now that we are done reading it, and return successfully
    fclose(rkt);
    return 0;
}

/**
 * handleAddress
 *
 * Extracts information from a virtual address and prints it out in the format expected by the assignment.
 * @param {int} n The n lowest significant bits that represent the offset
 * @param {int} m The next m bits that represent the page number; assume that n+m is always 16
 * @param {unsigned int} v The virtual address that needs to be mapped to a page number and offset
 */
int handleAddress(int n, int m, unsigned int v) {
    // Do n and m also have to be marked unsigned?
    int p = v >> n;
    int d = v & ~((~0) << n); // create a mask similar to: 00...00011111 with n 1's, then & v
    // could probably also use:
    // int d = (v << m) >> m;
    printf("virtual address %d is in page number %d and offset %d\n", v, p, d);
    return 0; // would return p and d in a struct here probably, but seems its not required for this project.
}
