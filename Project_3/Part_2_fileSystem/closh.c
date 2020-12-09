// closh.c - COSC 315, Winter 2020
// RACHELLE GELDEN
// JASPER LOOMAN
// BRIAN SU
// BRANDON UNGER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myFileSystem.c"

#define TRUE 1
#define FALSE 0
#define closhMode 0

int toInt(char c) {
    return c - '0';
}

//Random data generate for writing to file.
void generateData(char buf[1024], int number) {
    char alph[62]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTYVWXYZ0123456789";
    for (int i = 0; i < number; ++i) {
        buf[i] = alph[rand() % (sizeof(alph) - 1)];
    }
}

// main method - program entry point
int main() {
    FILE *fptr;

    char* cmdToken0 = {-1};
    char* cmdToken1 = {-1};
    char* cmdToken2 = {-1};
    int cmd1Flag = FALSE;
    int cmd2Flag = FALSE;
    size_t len = 0;

    FileSystem* fs;


    for(int i = 0; i < 3; i++){
        char* diskLine = NULL;

        if(closhMode){
            printf("Please enter disk: ");
            fflush(stdout);
            getline(&diskLine,&len, stdin);
        } else{
            fptr = fopen("lab3input.txt","r");
            if(fptr == NULL){
                printf("Faild to find script file, Exiting program.");
                goto end1;
            }
            getline(&diskLine,&len, fptr);
        }

        //remove the new line char from string
        diskLine = strtok(diskLine, "\n");
        if(!closhMode){
            diskLine = strtok(diskLine, "\r");
        }

        fs = createMyFileSystem(diskLine);
        if(fd > 0){
            break;
        } else if(i == 3){
            printf("Unable to find file three time, exiting program");
            goto end;
        }
    }



    while (TRUE) {
        char* line = NULL;
        char buf[1024] = {0};

        //reads next newLine
        if(closhMode){
            printf("closh>\n");
            fflush(stdout);
            getline(&line,&len, stdin);
        } else{
            getline(&line,&len, fptr);
        }

        //remove the new line char from string
        line = strtok(line, "\n");
        if(!closhMode){
            line = strtok(line, "\r");
        }
        if(line == NULL){
            goto end1;
        }

        //read command
        char *ptr = strtok(line, " ");
        cmdToken0 = malloc(strlen(ptr)*sizeof(char));
        strcpy(cmdToken0, ptr);

        //get filename
        ptr = strtok(NULL, " ");
        if(ptr != NULL){
            cmdToken1 = malloc(strlen(ptr)*sizeof(char));
            strcpy(cmdToken1, ptr);
            cmd1Flag = TRUE;
        }
        //get number
        ptr = strtok(NULL, " ");
        if(ptr != NULL){
            cmdToken2 = malloc(strlen(ptr)*sizeof(char));
            strcpy(cmdToken2, ptr);
            cmd2Flag = TRUE;
        }


        //command handling.
        if (strcasecmp(cmdToken0, "C") == 0 || strcasecmp(cmdToken0, "c") == 0) {
            if( !(cmd1Flag && cmd2Flag)){
                printf("Error invalid command arguments\n");
            }
            createFile(fs, cmdToken1, (int32_t) toInt( *cmdToken2));
        } else if (strcasecmp(cmdToken0, "D") == 0 || strcasecmp(cmdToken0, "d") == 0) {
            if(!cmd1Flag){
                printf("Error invalid command arguments\n");
            }
            deleteFile(fs,cmdToken1);
        } else if (strcasecmp(cmdToken0, "R") == 0 || strcasecmp(cmdToken0, "r") == 0) {
            if(!(cmd1Flag && cmd2Flag)){
                printf("Error invalid command arguments\n");
            }
            readFile(fs, cmdToken1, toInt( *cmdToken2), buf);
        } else if (strcasecmp(cmdToken0, "W") == 0 || strcasecmp(cmdToken0, "w") == 0) {
            if(!(cmd1Flag && cmd2Flag)){
                printf("Error invalid command arguments\n");
            }
            generateData(buf, 1000);
            writeFile(fs, cmdToken1, toInt( *cmdToken2), buf);
        } else if (strcasecmp(cmdToken0, "L") == 0 || strcasecmp(cmdToken0, "l") == 0) {
            listFiles(fs);
        } else if (strcasecmp(cmdToken0, "exit\n") == 0 || strcasecmp(cmdToken0, "exit") == 0) {
            goto end;
        }
        fflush(stdout);


    }
    end1:
    fclose(fptr);
    end:
    destroy();
}

