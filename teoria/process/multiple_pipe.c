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
	int fd[3][2];
	int n = 0;
	int i = -1;
	
	while (++i < 3)
	{
		if (pipe(fd[i]) < 0)
		{
			while (i--)
			{
				close(fd[i][0]);
				close(fd[i][1]);
			}
			return (1);
		}
	}

	int pid1 = fork();
	if (pid1 == -1)
		return (1);
	else if (pid1 == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][1]);
		close(fd[2][0]);
		read(fd[0][1], &n, sizeof(n));
		printf("Child 1 IN n = %d\n", n);
		n += 5;
		printf("Child 1 OUT n = %d\n", n);
		write(fd[1][1], &n, sizeof(n));
		close(fd[1][1]);
		return (0); //Ponemos return y asi no hay que hacer else
	}
	int pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		close(fd[0][1]);
		close(fd[0][0]);
		close(fd[1][1]);
		close(fd[2][0]);
		read(fd[1][0], &n, sizeof(n));
		printf("Child 2 IN n = %d\n", n);
		n += 5;
		printf("Child 2 OUT n= %d\n", n);
		write(fd[2][1], &n, sizeof(n));
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	close(fd[0][0]);
	close(fd[1][1]);
	close(fd[1][0]);
	printf("Parent IN n = %d\n", n);
	write(fd[0][1], &n, sizeof(n));
	close(fd[0][1]);
	read(fd[2][0], &n, sizeof(n));
	close(fd[2][0]);
	printf("Parent OUT n = %d\n", n);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
