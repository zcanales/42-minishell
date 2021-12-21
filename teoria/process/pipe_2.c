#include <stdio.h>	/*	printf , scanf */
#include <unistd.h>	/* write, read, close, fork, pipe*/
#include <sys/wait.h> /*wait */

/*Enviar inforacion entre processos. Así no se copia toda la info cuando se hae fork*/

int err(char *str, int err)
{
	if (str)
		printf("%s\n", str);
	return (err);
}

int main(int argc, char **argV)
{
	int arr[] = {1, 2, 3, 4, 1, 2, 7, 7};
	int arrSize = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];

	if (pipe(fd) == -1)
		return (err("Error: Pipe", 1));
	int id = fork();
	if (id == -1)
		return (err("Error: Fork", 2));
	if (id == 0)
	{
		start = 0;
		end = arrSize / 2;
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}
	int sum = 0;
	int i = start;
	while (i < end)
	{
		sum +=arr[i];
		i++;
	}
	printf("SumArr == %d\n", sum);
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(int)) == -1)
			err("Error: Writing", 3);
		close(fd[1]);
	}
	else
	{
		int sumFromChild;
		close(fd[1]);
		read(fd[0], &sumFromChild, sizeof(sumFromChild));
		close(fd[0]);
		printf("TotalSum == %d\n", sum + sumFromChild);
		wait(NULL);
	}
	return (0);
}
