/* 
Name: James Zhang
UID: 118843940
Directory ID: jzhang72
Professor Yoon, CMSC216
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "command.h"
#include "executor.h"

/* 
This recursive function handles different cases of shell commands that are
dependent on the `conjunction` field of the `tree` struct thanks to the the 
given lexer and parser. 
:param struct tree *t: a node in the parsed tree
:param int infd: otpional input file descriptor 
:param int outfd: optional output file descriptor
:return: EXIT_SUCCESS or EXIT_FAILURE
*/
int execute_helper(struct tree *t, int infd, int outfd) {

   if (t) {
      /* use file descriptors from the tree if they aren't null; otherwise
      use STDIN_FILENO and STDOUT_FILENO */
      int fd1 = t->input == NULL ? infd : open(t->input, O_RDONLY);
      int fd2 = t->output == NULL ? outfd: open(t->output, O_WRONLY | O_CREAT, 0664);
      
      /* let's first handle cases where the conjunction is NONE */
      if (t->conjunction == NONE) {
         /* let's first handle exit, then handle cd */
         if (strcmp(t->argv[0], "exit") == 0) {
            printf("See you.\n");
            exit(EXIT_SUCCESS);
         }
         else if (strcmp(t->argv[0], "cd") == 0) {
            /* if no location provided with cd, change dir to HOME */
            int err = t->argv[1] == NULL ? chdir(getenv("HOME")) : chdir(t->argv[1]);
            if (err == -1) {
               /* if this fails, we perror the location */
               perror(t->argv[1]);
               return EXIT_FAILURE;
            }
         } else {
            /* else we have to use execvp and forking to run the command */
            int pid = fork();
            if (pid < 0) {
               /* error */
               perror("fork");
               exit(EXIT_FAILURE);
            } else if (pid == 0) {
               /* child code (pid == 0) */
               int input_res, output_res;
               if (fd1 != STDIN_FILENO) {
                  input_res = dup2(fd1, STDIN_FILENO);
                  if (input_res < 0) {
                     /* if error, then raise the error */
                     perror("dup2");
                     exit(EXIT_FAILURE);
                  }
                  /* if no error, then we can close the file descriptor */
                  close(fd1);
               }
               /* same thing for output*/
               if (fd2 != STDOUT_FILENO) {
                  output_res = dup2(fd2, STDOUT_FILENO);
                  if (output_res < 0) {
                     perror("dup2");
                     exit(EXIT_FAILURE);
                  }
                  close(fd2);
               }
               /* now execute the command using execvp */
               execvp(t->argv[0], t->argv);
               /* no need for if statement */
               fprintf(stderr, "Failed to execute %s\n", t->argv[0]);
               exit(EXIT_FAILURE);
            } else {
               /* parent code that makes sure that the child exits successfully*/
               int status;
               wait(&status);
               if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
                  return EXIT_SUCCESS;
               } else {
                  return EXIT_FAILURE;
               }
            }
         }
      /* now let's handle other conjunctions, starting with PIPE */
      } else if (t->conjunction == PIPE) {
         /* we have to check first for ambiguous input and output first */
         if (t->right->input) {
            printf("Ambiguous input redirect.\n");
         } else if (t->left->output) {
            printf("Ambiguous output redirect.\n");
         } else {
            /* if two clear directions are specified, we can pipe */
            int pid_l, pid_r;
            int pipe_array[2];
            if (pipe(pipe_array) < 0) {
               /* error */
               perror("pipe");
               exit(EXIT_FAILURE);
            }
            /* if no error, fork for left side */
            pid_l = fork();
            if (pid_l < 0) {
               /* error */
               perror("fork");
               exit(EXIT_FAILURE);
            } else if (pid_l == 0) {
               /* child's code */
               close(pipe_array[0]);
               if (dup2(pipe_array[1], STDOUT_FILENO) < 0) {
                  perror("dup2");
                  exit(EXIT_FAILURE);
               }
               close(pipe_array[1]);
               /* recursively call helper on left tree */
               if (execute_helper(t->left, fd1, fd2) == EXIT_SUCCESS) {
                  exit(EXIT_SUCCESS);
               } else {
                  exit(EXIT_FAILURE);
               }
            } else {
               /* or fork a child for the left side (parent code) 
                  - this is basically the same code as above for the left child
                  */
               pid_r = fork();
               if (pid_r < 0) {
                  perror("fork");
                  exit(EXIT_FAILURE);
               } else if (pid_r == 0) {
                  /* child's code*/
                  close(pipe_array[1]);
                  if (dup2(pipe_array[0], STDIN_FILENO) < 0) {
                     perror("dup2");
                     exit(EXIT_FAILURE);
                  }
                  close(pipe_array[0]);
                  if (execute_helper(t->right, fd1, fd2) == EXIT_SUCCESS) {
                     exit(EXIT_SUCCESS);
                  } else {
                     exit(EXIT_FAILURE);
                  }
               } else {
                  /* Parent code, wait for all children to finish */
                  int status1, status2;
                  close(pipe_array[0]);
                  close(pipe_array[1]);
                  wait(&status1);
                  wait(&status2);
                  /* ensure that both exited correctly */
                  if (WIFEXITED(status1) & WIFEXITED(status2)) {
                     if (WEXITSTATUS(status1) == EXIT_SUCCESS &&
                         WEXITSTATUS(status2) == EXIT_SUCCESS) {
                        return EXIT_SUCCESS;
                     }
                  } else {
                     return EXIT_FAILURE;
                  }
               }
            }
         }
      /* now let's do AND conjunction */
      } else if (t->conjunction == AND) {
         int res = execute_helper(t->left, fd1, fd2);
         /* recall short circuiting; if left fails, then don't even call right*/
         if (res == EXIT_SUCCESS) {
            execute_helper(t->right, fd1, fd2);
         } else {
            return EXIT_FAILURE;
         }
      } else if (t->conjunction == SUBSHELL) {
         /* the commands should be run in a subshell */
         int pid = fork();
         if (pid < 0) {
            /* error code */
            perror("fork");
            exit(EXIT_FAILURE);
         } else if (pid == 0) {
            /* child's code */
            int res = execute_helper(t->left, fd1, fd2);
            if (res == EXIT_SUCCESS) {
               exit(EXIT_SUCCESS);
            } else {
               exit(EXIT_FAILURE);
            }
         } else {
            /* parent code should reap the child */
            int status;
            wait(&status);
            if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
               return EXIT_SUCCESS;
            } else {
               return EXIT_FAILURE;
            }
         }
      }
      return EXIT_SUCCESS;
   }
   return EXIT_FAILURE;
}


/* 
This function simply calls the recursive helper function execute_helper()
:param struct tree *t: a node in the parsed tree
:return: EXIT_SUCCESS or EXIT_FAILURE
*/
int execute(struct tree *t) {
   return execute_helper(t, STDIN_FILENO, STDOUT_FILENO); 
}

