/* 
 * File:   fshell.c
 * Authors: Sarah Sesek
	    Samuel Turnage
 * Created on April 7, 2015, 12:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

char pathname[200] = "/bin";
int i = 0;
int j, k;

void parse(char* input, char* arguments[]){
	arguments[0] = strtok(input, "\n ");
	i = 0;
	do{
		i++;
		arguments[i] = strtok(NULL, "\n ");
	}while(arguments[i] != NULL);  
}

char* path(char* arguments[]){
	char* ptr;
	char colonplus[50] = ":";
	int length, endsubstring;
	if(arguments[1] == NULL){
		printf("\n%s\n", pathname);
		return pathname; 
	}
	else if(strcmp(arguments[1], "+") == 0){
		if(arguments[2] == NULL){
			printf("\nTo append a string to the path you must include the string to append. Try again.\n");
			return pathname;
		}
		strcat(pathname, ":");
		strcat(pathname, arguments[2]);
		return pathname;
	}
	else if(strcmp(arguments[1], "-") == 0){
		if(arguments[2] == NULL){
			printf("\nTo remove a string from the path you must include the string to remove. Try again.\n");
			return pathname;
		}
		ptr = strstr(pathname, arguments[2]);
		length = strlen(arguments[2]);
		//in the path /usr/bin:/bin the substring /bin appears first in /usr/bin
		//to prevent problems like these make sure the substring is either the first path or is preceded by a colon
		if(ptr != pathname){
			strcat(colonplus, arguments[2]);
			ptr = strstr(pathname, colonplus);
			length = strlen(colonplus);
			endsubstring = ptr - pathname;
			endsubstring = endsubstring + length;
		}
		else{
			memcpy(colonplus, arguments[2], (length + 1));
			strcat(colonplus, ":");
			endsubstring = 0;
		}
		//if substring is in middle use memmove; remember the colon or 58 in ascii
		if(pathname[endsubstring] == 58){
			memmove((ptr + 1), (ptr + length + 1), (strlen(ptr + length + 1)+1));
		}
		else{
			//if substring is at end overwrite with null char
			strncpy(ptr, "\0", 1);
		}
		return pathname;
	}
	else{
		printf("Error: could not interpret 1st argument. Path not altered");
		return pathname;
	}
}


int main(int argc, char **argv) {
	char input[100];
	char* chrptr;
	char string[60] = "PATH="; 
	char *arguments[10];
	char *envp[2];
	int pid, checkwait, checkforerror, signum, status,fd;
	bool torf;
	strcat(string, pathname);
	envp[0] = string;
	envp[1] = NULL;
	while(1){
		printf("\nfloppy: ");
		chrptr = fgets(input, 100, stdin);
		if(chrptr == NULL){
			printf("\nError: could not read input\n");
		}
		fd = open("./imagefile.img", O_RDONLY);
		if(fd == -1)
		{
			printf("\nError: File imagefile.img could not be opened\n");
			exit(EXIT_FAILURE);
		}
		parse(input, arguments);
		if(strcmp(arguments[0], "cd") == 0){
			chdir(arguments[1]);
			printf("\nCurrent working directory is now %s\n", arguments[1]);
		}
		else if(strcmp(arguments[0], "path") == 0){
			path(arguments);
		}
		else if(strcmp(arguments[0], "exit") == 0){
			exit(EXIT_SUCCESS);
		}
		else{
			pid = fork();
			//Error checking: if pid is negative forking failed
			if(pid == -1){
				printf("fork failed");
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			else if(pid > 0){ 
				//parent waits
				checkwait = wait(&status);
				if(checkwait == -1){
					printf("Waiting on a child process failed.");
				}
				torf = WIFSIGNALED(status);
				if(torf == true){
					printf("Child was signaled and terminated");
					signum = WTERMSIG(status);
					printf("%d", signum);
				}
			}
			else
			{

				//child
				short redirected = 0;
                                int out;
				if(arguments[1] != NULL && strcmp(arguments[1], ">") == 0 && arguments[2] != NULL)
                                {
                                        out = open(arguments[2], O_CREAT,0666);
                                        dup2(out, 1);
                                        redirected = 1;
                                }
                                else if(arguments[2]!= NULL && strcmp(arguments[2], ">") == 0 && arguments[3] != NULL)   
                                {
                                        out = open(arguments[3], O_CREAT,0666);
                                        dup2(out, 1); 
                                        redirected = 1; 
                                }
                                //run the child command process                                                                                               

				checkforerror = execve(arguments[0], arguments, envp);
				if(checkforerror == -1) 
                                {
       					printf("\n %s There was an error executing your last command."
						"\nCheck that you typed name of the command and its arguments are correctly. "
						"\nType help for the help command if you are stuck.\n", arguments[0]);
				}
				if(redirected==1)close(out);
			}
		}
	}
	return 0;
}
