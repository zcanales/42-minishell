#include <stdio.h>  /*  printf , scanf */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

int main(void)
{
	int fd[2];
	
	pipe(fd);
	int pid1 = fork();
	if (pid1 == -1)
		return (1);
	else if (pid1 == 0)
	{
		dup2(fd[1], 0);
		close(fd[0]);
		close(fd[1]); //borramos el que nos sobra
		execlp("ping", "ping", "-c", "1", "google.com", NULL);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		dup2(fd[0], 1);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
