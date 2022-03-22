
#include <stdio.h>
#include <string.h>

unsigned char password[14] = "";

int check_password(char *ptr){
    if (strlen(ptr) >= 14){
        for (int i=0; i < 14; i++){
            password[i] = ((ptr[i]) ^ 0x44) - 5;
        }
        if ((unsigned int)password[0]+(unsigned int)password[12] == 0x43 &&
            (unsigned int)password[1]+(unsigned int)password[2] == 0x94 &&
            (unsigned int)password[3]+(unsigned int)password[5] - (unsigned int)password[4]== 0x7e &&
            ((unsigned int)password[7]-(unsigned int)password[6]) + ((unsigned int)password[12]-(unsigned int)password[13]) == 0x72 &&
            ((unsigned int)password[8]-(unsigned int)password[10]) + ((unsigned int)password[11]-(unsigned int)password[9]) == 0x41 ){
                return 0;
            }
        return 1;
    }
    return 1;
}

int main(int argc,char *argv[]){
    if(argc < 2){
        printf("Enter the password as an argument.");
        return 1;
    }
    if (check_password(argv[1]) ){
        printf("incorrect password\n");
    }else{
        printf("correct password\n");
    }
    return 0;
}