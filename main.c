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

void exeCmd(char* line)
{
	char program[512];				//holds the command with path
	char *envp[] = { (char *) "PATH=/bin", 0 };  //environment variable
	char* holder[100];		//holds the tokens from strtok
	char* aToken;			//for strtok;
	char* param[100];			//holds the parameters for the command
	char cmd[100];				//holds the command
	int i = 0;				//for keeping count of elements
	//splitting arguments from command
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
	//running the command
	strcpy(program, "/bin/");		//initialize program with path
	strcat(program, cmd);	//add command to end of path
	int pid = fork();              //fork child
		if(pid==0)
		{               //Child
			execve(program, param, envp); //execute command
			exit(0);
		}
		else
		{
			wait(NULL);
		}
}		

void cd(char* buffer, char* token){                          //function to perfrom change directory
	token=strchr(buffer, ' ');

    if(token){
        char *tempToken = token + 1;                        //tokenize the original string to be able to seperate cd and the path
        token = tempToken;
        char *newLine = strchr(token, '\n');
            if(newLine) {
                *newLine = '\0';
				}
					chdir(token);				           //perform cd using chdir() and the path as the argument
		}
		else{		
				chdir(getenv("HOME"));	//go to home directory if token is empty
			}
}

void exitShell(char* line)
{
	char* tToken;					//for the strtok function
	int cmdCount = 0;				//counts the amount of commands
	char* commandHolder[20];		//holds the commands
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
				commandHolder[cmdCount] = tToken;		//store the command in the holder array
				cmdCount++;								//increment count of commands
			}
		}
		else
		{
			if(strstr(tToken, "exit") != NULL)	//if it is the exit command, do nothing until end
			{
			}
			else
			{
				commandHolder[cmdCount] = tToken;		//store the command in the holder array
				cmdCount++;								//increment count of commands
			}
		}
		tToken = strtok (NULL, ";\n");
	}
	  
	for(int i = 0; i < cmdCount; i++)		//execute each command
	{
		exeCmd (commandHolder[i]);					//execute the command
	}
	
	  exit(0);          //exit shell when all commands proccessed
}

void cmdProcess(char* line)  //function based on exit function, to execute commands without exitting
{
	char* tToken;					//for the strtok function
	int cmdCount = 0;				//counts the amount of commands
	char* commandHolder[20];		//holds the commands
	tToken = strtok (line,";\n");		//first split
	while (tToken != NULL)            //extract commands
	{
		if(tToken[0] == ' ')
		{	
			memmove (tToken, tToken+1, strlen (tToken+1) + 1); // get rid of space in string
			commandHolder[cmdCount] = tToken;		//store the command in the holder array
			cmdCount++;								//increment count of commands
		}

		else
		{
			commandHolder[cmdCount] = tToken;		//store the command in the holder array
			cmdCount++;								//increment count of commands
		}
		tToken = strtok (NULL, ";\n");
	}
	  
	for(int i = 0; i < cmdCount; i++)		//execute each command
	{
		exeCmd (commandHolder[i]);					//execute the command
	}
	
}

void pipe_func(char *buffer){		//ends program if you try to pipe ;-;
		char* token;				//keeps track of the arguments
		int p[2], pid;				//variables for process
		token=strtok(buffer, " ");	//seperates buffer by spaces
		for(int i=0; i<3; ++i){		//loops for 3 args
				pipe(p);			
				if(pid== fork() ==0){	//fork
					while(token != NULL){		//loop through arguments
						if(strcmp(token, "|") && token != NULL){	//if there's a bar dont do this
							//char* temp = token;
							//printf("%s\n", temp);
							dup2(p[1], 1);
							execlp(token, token, NULL);	//executes the current arg
							perror("exec");
							abort();
							}
					}
				
				}
				else {
					wait(NULL);
				}

				dup2(p[0], 0);
				close(p[1]);
		}
		
		while(token != NULL){		
			if(strcmp(token, "|") && token != NULL){
				execlp(token, token, NULL);
				perror("exec");
				abort();
			}
		}

}
int main(){

    char* buffer;
    char* token;
    token = strtok (buffer,";\n");	//use token to be able to seperate the buffer
	char prompt[]="prompt D";	//set prompt
	char choice[]="no";			//initialize choice to no		
	printf("Customize shell prompt (extra credit) (Type yes or no): "); 
	fgets(choice, 100, stdin); //lets us know if the user wants to change
	if((strcmp(choice, "yes")) > 0){	//if user wants to change, get the new prompt and remove the \n due to fgets
		printf("Enter prompt: ");
		fgets(prompt, 100, stdin);
		strtok(prompt, "\n");
	}
	else{
		strcpy(prompt, "prompt D");
	}
	
	while(1){                           //while buffer != exit perform each command		//strncmp(buffer, "exit", 4) !=0

		printf("%s: ", prompt);                                          //print prompt and get user input
		fgets(buffer, 100, stdin);

		if(strstr(buffer, "exit") != NULL)  //if input line contains exit, execute commands and exit
		{
			exitShell(buffer);
		}
		
		if(strstr(buffer, "cd") != NULL){                            //if cd is in the buffer, perform cd function       
			cd(buffer, token);
        }
		if(strstr(buffer, "|") != NULL){
			pipe_func(buffer);
		}
		else{
		cmdProcess(buffer);			//otherwise, process commands
		}
    }

    return 0;
}
