#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
    
int main(int argc, char** argv) {
    char c1[30];
    char c2[30];
    char c3;
    char c4[30];
    char c5[30];

    printf("WELCOME<SHELL>\n");
    printf("enter cat ./tt.c | grep main\n or something else with same format [command] [argument or path] | [command] [argument or path]\n");
    while(1)
    {
    printf("shell~::~$");
    scanf("%s %s %c %s %s",c1,c2,&c3,c4,c5);
    int fd[2];
    if (pipe(fd) != 0) {
       printf ("Error creating pipe. %s", strerror(errno));
       exit(errno);
    }
        
    int pid = fork();
    if (pid == -1) {
       printf ("Error creating pipe. %s", strerror(errno));
       exit(errno);
    } else if (pid == 0) {
       //child        
       /* Replace standard output of child process with read end of the pipe */
        dup2(fd[0], 0);
            
        /* Close the write end of the pipe in child process.It is not used */
         close(fd[1]);         /* Close the read end of the pipe in child process. We have a copy of it in file descriptor 0*/
         close(fd[0]);         execlp(c4, c4, c5, NULL);
     } else {
        //parent
        /* Replace standard output of parent process with write end of the pipe */
        dup2(fd[1], 1);
            
        /* Close the read end of the pipe in parent process.It is not used */
         close(fd[0]);
            
         /* Close the write end of the pipe in child process.We have a copy of it in file descriptor 1*/
          close(fd[1]);   
                        
          execlp(c1, c1 , c2 , NULL);        
     }
    }
}