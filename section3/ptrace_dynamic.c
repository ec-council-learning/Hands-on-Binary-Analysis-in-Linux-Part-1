#include <stdlib.h>
#include <stdio.h>
#include<sys/ptrace.h>
#include <dlfcn.h>
#include <string.h>

int main(int argc, char **argv) {
    void *handle;
    long (*pt)(enum __ptrace_request request, pid_t pid);

    handle = dlopen ("/lib/x86_64-linux-gnu/libc.so.6", RTLD_LAZY);
    pt = dlsym(handle, "ptrace");

    if (pt(PTRACE_TRACEME, 0) < 0) {
        printf("Debugger detected!\n");
	exit(1);
    }

    printf("Normal execution\n");
    dlclose(handle);
    
    return 0;
}