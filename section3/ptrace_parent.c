#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main() {
    
    pid_t child_pid = fork();
    if (child_pid == 0){ /* child process */
        pid_t parent_pid = getppid();
        if( ptrace( PTRACE_ATTACH, parent_pid, 0, 0 ) < 0 ) {
            printf("Debugger detected!\n");
            exit(1);
        }
        waitpid( parent_pid, NULL, 0 );
        ptrace( PTRACE_CONT, parent_pid, 0, 0 );
        ptrace( PTRACE_DETACH, parent_pid, 0, 0 );
        printf("Normal execution\n");
        
    } else { /* parent process */
        wait(NULL);
    } 
    
    return 0;
}