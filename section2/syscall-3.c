#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
void main(){
    syscall(SYS_write, 1, "Hello World!\n", 13);
}