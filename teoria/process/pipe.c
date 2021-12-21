#include <stdio.h>	/*	printf , scanf */
#include <unistd.h>	/* write, read, close, fork, pipe*/

/*Enviar inforacion entre processos. Así no se copia toda la info cuando se hae fork*/

int err(char *str, int err)
{
	if (str)
		printf("%s\n", str);
	return (err);
}
int main(int argc, char **argV)
{
	/* 
	 * Two integers, fd for pipe
	 * 1. Do pipe
	 * 	fd[0] - read hand
	 * 	fd[1] - write hand
	 * 2. Copy over fork -> inherit the fd pipe. Copy over and indepdendant of each other
	 * */
	int fd[2];
	if (pipe(fd) == -1)
		return (err("Error: Pipe", 1));
	int id = fork();
	if (id == -1)
		return (err("Error: Fork", 1));
	if (id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
			err("Error: Writing", 1);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1)
			return (err("Error: Reading", 1));
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	return (0);
}
