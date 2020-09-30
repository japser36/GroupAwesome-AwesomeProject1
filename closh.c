// closh.c - COSC 315, Winter 2020
// YOUR NAME HERE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char *cmd, char **cmdTokens) {
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

// execution function, used to simplify the code
void exe(const char *_file, char *const cmdTokens[]){
    printf("Current pid =%d\n", getpid());
    fflush(stdout);
    execvp(_file, cmdTokens); // replaces the current process with the given program
    printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
    fflush(stdout);
    exit(1);
}
// signal handing function.
// is call when the alarm triggers the signal.
void handler(int num){
    printf("Program timed out\n");
    fflush(stdout);
    exit(1);
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char *cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    pid_t childPid; // pid for last child created by parent.
    int status = 0;

    while (TRUE) { // main shell input loop

        // begin parsing code - do not modify
        printf("closh> ");
        // fflush(stdout) was added to all output of the program in order to support a bug in the IDE
        fflush(stdout);
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
        readCmdTokens(cmd, cmdTokens);
        do {
            printf("  count> ");
            fflush(stdout);
            count = readChar() - '0';
        } while (count <= 0 || count > 9);

        printf("  [p]arallel or [s]equential> ");
        fflush(stdout);
        parallel = (readChar() == 'p') ? TRUE : FALSE;
        do {
            printf("  timeout> ");
            fflush(stdout);
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code


        ////////////////////////////////////////////////////////
        //                                                    //
        // TODO: use cmdTokens, count, parallel, and timeout  //
        // to implement the rest of closh                     //
        //                                                    //
        // /////////////////////////////////////////////////////


        while (count > 0) {
            //fork will return childpid on parent and 0 on child.
            childPid = fork();
            if (childPid == 0) {
                //sets the signal handler to fire when the time out occurs.
                signal(SIGALRM, handler);
                //sets the alarm for the signal. By def alarm of (0) will cancel the active timer.
                alarm(timeout);
                //This is a simplified function for execution
                exe(cmdTokens[0], cmdTokens);
            } else {
                count--;
                //fi parallel we want to wait until the last command has finished before running the next command
                if(!parallel){
                    //Makes the parent stop execution and wait on the child to finish
                    waitpid(childPid,NULL, 0);
                }
            }
        }
        //found at https://stackoverflow.com/questions/19461744/how-to-make-parent-wait-for-all-child-processes-to-finish
        //this will wait until any child presses to finish, then returns the pid of the child.
        //If there is no child that is running it will return 0. This runs until there is no more child processes.
        while (wait(&status) > 0);
    }
}

