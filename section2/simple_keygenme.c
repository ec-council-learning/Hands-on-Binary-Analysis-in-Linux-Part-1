#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2){
        return 1;
    }
    char universal_pass[] = "S1MPL3_p422W0rd" ;
    char input_pass[20];
    strncpy(input_pass, argv[1], sizeof(input_pass));
    for (int i=0;  i < strlen(universal_pass); i++){
        if (strcmp(&universal_pass[i], &input_pass[i]) != 0){
            printf("Wrong password!\n");
            return 1;
        }
    }
    printf("You got it!\n");
    return 0;
}