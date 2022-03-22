/* 

  Compile : gcc -static -o memory_laout memory_layout.c 

64-bit process virtual address space :
==============================================================================================================================
    Start addr       |   Offset   |     End addr        |  Size   | VM area description
==============================================================================================================================
                     |            |                     |         |
 0000_0000_0000_0000 |    0       | 0000_7fff_ffff_ffff |  128 TB | user-space virtual memory
_____________________|____________|_____________________|_________|___________________________________________________________
                     |            |                     |         |
 0000_8000_0000_0000 | +128    TB | ffff_7fff_ffff_ffff | ~16M TB | ... huge, almost 64 bits wide hole of non-canonical
                     |            |                     |         |     virtual memory addresses up to the -128 TB
                     |            |                     |         |     starting offset of kernel mappings.
_____________________|____________|_____________________|_________|___________________________________________________________

*/

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

char *environ;
char *string = "junk string";
int MALLOC_SIZE = 32;


void func1(void);
void func2(void);

// int main(void) {
// int main(int argc, char **argv) {
int main(int argc, char **argv, char **envp) {

	char *ptr1, *ptr2;

    printf("Text Segment:\n");
	printf("-------------------------\n");
	printf("%#018lX  main function\n", (unsigned long)&main);
    printf("%#018lX  func1 function\n", (unsigned long)&func1);
	printf("%#018lX  func2 function\n\n", (unsigned long)&func2);

	printf("Initialized Data:\n");
	printf("-------------------------\n");
	printf("%#018lX initialized global char *string\n\n", (unsigned long)&string);

	printf("Uninitialized Data (BSS):\n");
	printf("-------------------------\n");
	printf("%#018lX  uninitialized global char *environ\n\n", (unsigned long)&environ);

	printf("Stack:\n");
	printf("-------------------------\n");
	printf("%#018lX  argc\n", (unsigned long)&argc);
	printf("%#018lX  argv\n", (unsigned long)&argv);
	printf("%#018lX  envp\n", (unsigned long)&envp);
    func1();
    printf("\n");

	printf("Heap:\n");
	printf("-------------------------\n");
	ptr1 = malloc(MALLOC_SIZE);
    ptr2 = malloc(MALLOC_SIZE);
    printf("%#018lX  ptr1 area begins\n", (unsigned long)ptr1);
	printf("%#018lX  ptr1 area ends\n", (unsigned long)ptr1+MALLOC_SIZE);
    printf("%#018lX  ptr2 area begins\n", (unsigned long)ptr2);
	printf("%#018lX  ptr2 area ends\n\n", (unsigned long)ptr2+MALLOC_SIZE);
	free(ptr1);
    free(ptr2);

	return 0;
}

void func1(void) {
	int tmp;
	printf("%#018lX  func1 stack frame\n", (unsigned long)&tmp);
    func2();
}

void func2(void) {
	int tmp;
	printf("%#018lX  func2 stack frame\n", (unsigned long)&tmp);
}

