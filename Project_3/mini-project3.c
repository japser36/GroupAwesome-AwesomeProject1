#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

FILE *fptr;

int main(int argc, char *argv[]){
    fptr = fopen("fileopen","mode");
    fopen("..\\GroupAwesome-AwesomeProject1\\Project_3\\lab3input.txt","r");
    


    fclose(fptr);
    return 0;
}

