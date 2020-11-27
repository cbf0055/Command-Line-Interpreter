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

void exitShell(char* line)
{
	char* tToken;					//for the strtok function
	char* path = "/bin/";
	char* command;
	char* fullLine;
	int pid;
	int cycle = 0;
	tToken = strtok (line,";\n");		//first split
	  while (tToken != NULL)            //extract commands
	  {
		cycle++;
		if(tToken[0] == ' ')
		{	
			memmove (tToken, tToken+1, strlen (tToken+1) + 1); // get rid of space in string
			if(strstr(tToken, "exit") != NULL)
			{
			}
			else
			{
				printf ("Cycle %d: %s\n",cycle, tToken);    //print to show that command was extracted (for testing)
			}
		}
		else
		{
			if(strstr(tToken, "exit") != NULL)
			{
			}
			else
			{
				printf ("Cycle %d: %s\n",cycle, tToken);   //print to show that command was extracted (for testing)
			}
		}
		tToken = strtok (NULL, ";\n");
	  }
	  
	  exit(0);          //exit shell when all commands proccessed
}
int main(){

    char* buffer;
    char* token;
    token = strtok (buffer," ");                                     //use token to be able to seperate the buffer
   
    while(1){                           //while buffer != exit perform each command		//strncmp(buffer, "exit", 4) !=0

		printf("prompt D: ");                                           //print prompt and get user input
		fgets(buffer, 100, stdin);

		if(strstr(buffer, "cd") != NULL){                            //if cd is in the buffer, perform cd function       
            cd(buffer, token);
        }

        if(strstr(buffer, "ls") != NULL){                             //used to see if cd works properly
            system("ls");
        }
		
		if(strstr(buffer, "exit") != NULL)
		{
			exitShell(buffer);
		}
   
    }
   

    return 0;
}
