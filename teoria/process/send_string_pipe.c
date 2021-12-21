#include <stdio.h>  /*  printf , scanf */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

// 2 process
// 	1) Child process should generate random numbers and send them
// 	to the parent
// 	2) Parent is going to sum all the numbers and print the result

int main(void)
{
	int fd[2];
	char str[200];
	int i = -1;
	int n;
	pipe(fd);
	int pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd[0]);
		printf("Input string: ");
		fgets(str, 200, stdin);
		str[strlen(str) - 1] = '\0';
		n = strlen(str) + 1;
		write(fd[1], &n, sizeof(int));
		write(fd[1], &str, sizeof(char) * n);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		read(fd[0], &n, sizeof(int));
		read(fd[0], &str, sizeof(char) * n);
		close(fd[1]);
		printf("\nSuma total = %s\n", &str[0]); 
		wait(NULL);

	}
}
