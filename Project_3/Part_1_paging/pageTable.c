#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

FILE *rkt;

int main(int argc, char *argv[]){
    // This will store user name for the file that they wish to open and read 
    char filePath[255];
    char fileData[255];
    int lineNumber = 128;

    // Getting user input for the file path to read into bitwise processor
    printf( "Enter the address of the input file : ");
    // using a string format input via scanf
    scanf("%s", filePath);

    // varify the input, by printing the filepath back to the user
    printf( "\nYou entered: ");
    puts(filePath);

    // File open attempt and varification of file opened below
    rkt = fopen(filePath,"r");
    // If the file is not opened, return an error for the user to correct their mistake
    if (rkt == NULL) {
        printf("\nError while loading the file\n");
        exit(1);
    }
      
    // this prints the first line of the test file
    // read the line in strings
       fscanf(rkt,"%s", fileData);
    // prints the file data in the output
      printf("Value of the test is %s \n", fileData);

    // Switched the break condition to EOF as per fscanf design instead of using the previous
    // fscanf(rkt, "%s ", fileData)!= 1 which seemed to cause issues in the sustem
    while(fscanf(rkt, "%s ", fileData)) {
        // prints the file data in the output
        printf("Value of the test is %s\n", fileData);
        // read the line in strings
        fscanf(rkt,"%s ", fileData);
        // if the reader has encountered EOF then break 
        if(feof(rkt)){
          break;
        } else {
          // prints the file data in the output
        printf("Value of the test is %s\n", fileData);
        }
      }   
    
    // Idea for eof was inspired by this: 
    // https://stackoverflow.com/questions/1835986/how-to-use-eof-to-run-through-a-text-file-in-c
      
      

    fclose(rkt);
    return 0;
}
typedef struct {

} PageTable;

PageTable createPageTable(){

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







// Scraped attempt working attempt is above
    // An attempt to do..while for better execution, the if-statement will be triggered at EOF or error
    // terminating the do..while
    // currently it is reading the file short or at random places 
    // the test input file is called test.txt
    /*
    do {
      // read the line in strings
      fscanf(rkt,"%s", fileData);

      // prints the file data in the output
      printf("Value of the test is %s at line \n", fileData);
    } while((fscanf(rkt, "%s", fileData) != 1));
    */