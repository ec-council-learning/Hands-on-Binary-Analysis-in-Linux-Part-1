#include <stdio.h>
#include <sys/ptrace.h>

int main(){
    if (ptrace(PTRACE_TRACEME, 0,0,0)<0){
        printf("Debugger Detected!\n");
        return 1;
    }else{
        printf("Normal Execution\n");
    }
    return 0;
}