#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cd(char* buffer, char* token){                             //function to perfrom change directory
    token=strchr(buffer, ' ');
    if(token){
        char *tempToken = token + 1;                               //tokenize the original string to be able to seperate cd and the path
        token = tempToken;
        char *newLine = strchr(token, '\n');
            if(newLine) {
                *newLine = '\0';
                }
                chdir(token);                                        //perform cd using chdir() and the path as the argument
        }
}
int main(){

    char* buffer;
    char* token;
    token = strtok (buffer," ");                                     //use token to be able to seperate the buffer
   
    while(strncmp(buffer, "exit", 4) !=0){                           //while buffer != exit perform each command

    printf("prompt D: ");                                           //print prompt and get user input
    fgets(buffer, 100, stdin);

        if(strstr(buffer, "cd") != NULL){                            //if cd is in the buffer, perform cd function       
            cd(buffer, token);
        }

        if(strstr(buffer, "ls") != NULL){                             //used to see if cd works properly
            system("ls");
        }
   
    }
   

    return 0;
}
