#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int pipeline(char **command) {
	char **cmd = command;
	while (*cmd != NULL) {
		if (!strcmp(*cmd, "|")) {
			return 1;
		}
		cmd++;
	}
	return 0;
}

int redirection(char **command) {
	char **cmd = command;
	while (*cmd != NULL) {
		if (!strcmp(*cmd, ">")) {
			return 1;
		}
		cmd++;
	}
	return 0;
}


int main()
{

	int i;
	char **cmd;
	char **cmmnd;
	char **pipe_command;
	char buf[512];
	int command_bytes;
	int pipe_fd[2];
	int redirect;
	int pipea;
	int fd;
	

    while (1) {
        char arg[50], mod[50];

        fprintf(stdout, "\nfloppy: ");
        fflush(stdout);


	//reset the pipe and redirect value
        pipea = 0;
        redirect = 0;

        cmd = (char **)malloc(20*sizeof(char *));
		for (i = 0; i < 20; i++) {
			cmd[i] = (char *) malloc(128);
		}

		if ((command_bytes = read(0, buf, 512)) < 0) {
			fprintf(stdout, "can't read the command, try again\n");
			break;
		}}
		pipea = pipeline(cmd);
		redirect = redirection(cmd);
		if (pipea > 0) {
			cmmnd = cmd;
			while (*cmmnd != NULL) {
			if (!strcmp(*cmmnd, "|")) {
			pipe_command = cmmnd + 1;
			*cmmnd = NULL;
			break;}
			cmmnd++;}
			if (redirect > 0) {
			cmmnd = pipe_command;
			while (*cmmnd != NULL) {
				if (!strcmp(*cmmnd, ">")) {
					if ((fd = open(*(cmmnd+1), 
						(O_WRONLY | O_CREAT | O_TRUNC), 0644)) < 0)
					fprintf(stdout, "can't make file for redirection\n");
						*cmmnd = NULL;
							break;
						}
						cmmnd++;
					}
				}
				if (*pipe_command == NULL || pipe_command[0][0] == '\0') {
					fprintf(stdout, "there is an error\n");
					fflush(stdout);
							
				if ((pipe(pipe_fd)) != 0){
					fprintf(stdout, "there is an error\n");
					}
				if ((fork()) == 0) {
					close(1);
                                        dup(pipe_fd[1]);
                                        close(pipe_fd[1]);
                                        close(pipe_fd[0]);
					execve(cmd[0], cmd, NULL);
					fprintf(stdout, "invalid command\n");
				}
				if ((fork()) == 0) {
					close(0);
                                        dup(pipe_fd[0]);
                                        close(pipe_fd[0]);
                                        close(pipe_fd[1]);
					if (redirect) {
                                            close(1);
                                            dup(fd);
                                            close(fd);
    					fprintf(stdout, "the error in pipe command\n");
				}
				close(pipe_fd[0]);
                                close(pipe_fd[1]);
				wait(NULL);
                                wait(NULL);
			}
			else {
				if (redirect > 0) {
					cmmnd = cmd;
					while (*cmmnd != NULL) {
						if (!strcmp(*cmmnd, ">")) {
							if ((fd = open(*(cmmnd+1), 
							(O_WRONLY | O_CREAT | O_TRUNC), 0644)) < 0)
						fprintf(stdout, "you can't create the file of redirect\n");
							*cmmnd = NULL;
							break;}						
						cmmnd++;}}
				if ((fork()) == 0) {
					if (redirect) {
						close(1);
            dup(fd);
            close(fd);}
					execve(cmd[0], cmd, NULL);}
				if (redirect){
					close(fd);
				wait(NULL);}
			}
		}
        free(cmd);
    }
return 0;}
