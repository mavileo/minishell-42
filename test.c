/* 
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]){
	pid_t		pid;
	int			status;
	int			fds[2];
	int i;
	char buf[100];

	if (argc < 2)
    	return 1;
	if (pipe(fds) == -1)
		return (1);
	if ((pid = fork()) == 0)
	{
		close(fds[0]);
		if ((i = dup2(fds[1], 1)) == -1)
			return (1);
		execve(argv[1], (argv + 1), NULL);
		close(fds[1]);
	}
	else
 	{
		char *ag[] = {"/bin/grep", "watchdogd", NULL};
		waitpid(pid, &status, 0);
		close(fds[1]);
		if ((i = dup2(fds[0], 0)) == -1)
			return (1);
		execve(ag[0], (ag), NULL);
		close(fds[0]);
	}
	return (0);
}
 */