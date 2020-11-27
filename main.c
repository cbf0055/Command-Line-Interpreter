#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getArg(char* line, char cmd[], char* param[])
{
	char* holder[100];		//holds the tokens from strtok
	char* aToken;			//for strtok;
	int i = 0;				//for keeping count of elements
	
	aToken = strtok (line," ");		//split into first token
	while (aToken != NULL)
	{
		holder[i] = strdup(aToken);	//store into holder array
		i++;						//increment count
		aToken = strtok (NULL, " \n");		//move to next token
	}
	
	strcpy(cmd, holder[0]);	//first word in holder will be the command
	
	for(int j = 0; j < i; j++)		//store the contents of array in parameter array, add null terminator at the end
	{
		param[j] = holder[j];
		param[i] = NULL;
	}
}

	

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
	char command[100];				//holds the command
	char program[512];				//holds the command with path
	char* parameters[100];			//holds the parameters for the command
	int pid;
	char *envp[] = { (char *) "PATH=/bin", 0 };  //environment variable
	tToken = strtok (line,";\n");		//first split
	  while (tToken != NULL)            //extract commands
	  {
		if(tToken[0] == ' ')
		{	
			memmove (tToken, tToken+1, strlen (tToken+1) + 1); // get rid of space in string
			if(strstr(tToken, "exit") != NULL)  //if it is the exit command, do nothing until end
			{
			}
			else
			{
				getArg (tToken, command, parameters);	//split command and arguments
				strcpy(program, "/bin/");		//initialize program with path
				strcat(program,command);	//add command to end of path
				int pid= fork();              //fork child
				if(pid==0)
				{               //Child
					execve(program, parameters, envp); //execute command
					exit(0);
				}
				else
				{
					wait(NULL);
				}
			}
		}
		else
		{
			if(strstr(tToken, "exit") != NULL)	//if it is the exit command, do nothing until end
			{
			}
			else
			{
				getArg (tToken, command, parameters);	//split command and arguments
				strcpy(program, "/bin/");		//initialize program with path
				strcat(program,command);	//add command to end of path
				int pid= fork();              //fork child
				if(pid==0)
				{               //Child
					execve(program, parameters, envp); //execute command
					exit(0);
				}
				else
				{
					wait(NULL);
				}
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
