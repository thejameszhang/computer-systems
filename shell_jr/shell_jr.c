/* 
Name: James Zhang
UID: 118843940
Director ID: jzhang72
*/

#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <err.h>
#include <sys/types.h>

#define MAX_LENGTH 1024
#define MAX_STACK_SIZE 16
#define SUCCESS 1
#define FAILURE

/* Declare global variables related to the stack. */
char *stack[MAX_STACK_SIZE];
int top = 0;

/* 
This function checks if the stack is empty or not. 
:return: if the stack is empty or not
*/
int is_empty() {
    return (top == 0) ? 1 : 0;
}

/* 
This function checks if the stack is full or not.
:return: if the stack is full or not
*/
int is_full() {
    return (top == MAX_STACK_SIZE) ? 1 : 0;   
}

/* This function pushes the current directory to the stack. */
void push(char *arg) {
    if (is_full()) {
        printf("Directory stack is full\n");
    } else {
        char cwd[MAX_LENGTH];
        getcwd(cwd, MAX_LENGTH);
        if (chdir(arg) != -1) {
            stack[top] = malloc(strlen(cwd));
            strcpy(stack[top], cwd);
            top++;
        } else {
            printf("Cannot change to directory %s\n", arg);
        }
    } 
}

/* This function returns and pops the top directory from the stack. */
void pop() {
    if (is_empty()) {
        printf("Directory stack is empty\n");
    } else {
        if (chdir(stack[top - 1]) == -1) {
            printf("Cannot change to directory %s\n", stack[top - 1]);
        } else {
        }
        free(stack[top - 1]);
        top--;
    }
}

/* This function uses execvp() to execute the shell command. */
void use_execvp(int num_args, char *cmd, char *arg) {

    /* Declare local variables */
    char *argv[3];
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork error");
    }
    /* parent code */
    if (pid) {
        wait(NULL);
    } 
    /* child code */
    else {
        argv[0] = cmd;
        if (num_args == 1) {
            argv[1] = NULL;
        }
        if (num_args == 2) {
            argv[1] = arg;
            argv[2] = NULL;
        }
        execvp(cmd, argv);
        printf("Failed to execute %s\n", cmd);
        exit(EX_OSERR);
    }
}

/* 
This function takes in both the command and argument as input and conducts the 
appropriate shell command.

:param int num_args: number of correctly assigned arguments from sscanf()
:param char *cmd: the shell command
:param char *arg: the argument to the shell command
*/
void process_command(int num_args, char *cmd, char *arg) {
    
    /* Declare local variables. */
    int i;
    int res;

    /* exit or goodbye. */
    if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "goodbye") == 0) {
        printf("See you\n");
        fflush(stdout);
        exit(0);
    }
    /* cd: assume the argument (path) is always valid. */
    else if (strcmp(cmd, "cd") == 0) {
        if (num_args == 2) {
            res = chdir(arg);
            if (res == -1) {
                printf("Cannot change to directory %s\n", arg);
            }
        } else {
            printf("Failed to execute cd\n");
        }
    }
    /* pushd */
    else if (strcmp(cmd, "pushd") == 0) {
        if (num_args == 2) {
            push(arg);
        } else {
            printf("Failed to execute pushd\n");
        }
    }
    /* dirs */
    else if (strcmp(cmd, "dirs") == 0) {
        if (num_args == 1) {
            for (i = 0; i < top; i++) {
                printf("%s\n", stack[i]);
            }
        } else {
            printf("Failed to execute dirs\n");
        }
    }
    /* popd */ 
    else if (strcmp(cmd, "popd") == 0) {
        if (num_args == 1) {
            pop();
        } else {
            printf("Failed to execute popd\n");
        }
    }
    /* otherwise, use execvp() */ 
    else {
        use_execvp(num_args, cmd, arg);
    }
}

int main() {

    /* Declare the following local variables. */
    FILE *input = stdin;
    char line[MAX_LENGTH + 1], cmd[MAX_LENGTH + 1], arg[MAX_LENGTH + 1];
    int num_args;

    /* Print the first prompt. */
    printf("shell_jr: ");
    fflush(stdout);

    /* Read line by line. */
    while (fgets(line, MAX_LENGTH + 1, input) != NULL) {
        /* Process the line into first and second arguments. */
        num_args = sscanf(line, " %s %s ", cmd, arg);

        process_command(num_args, cmd, arg);
        
        /* Reset the buffers. */
        strcpy(cmd, "\0");
        strcpy(arg, "\0");
        printf("shell_jr: ");
        fflush(stdout);
    }
    fclose(input);
    return 0;
}