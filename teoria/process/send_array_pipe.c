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
	int i = -1;
	int n;
	pipe(fd);
	int pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd[0]);
		int arr[5];
		n = 5;
		write(fd[1], &n, sizeof(int));
		srand(time(NULL));
		while (++i < n)
		{
			arr[i] = rand() % 10;
			printf("%d ", arr[i]);
		}
		write(fd[1], &arr, sizeof(int) * n);
		close(fd[1]);
	}
	else
	{
		int sum[5];
		int sum_tot = 0;
		close(fd[1]);
		read(fd[0], &n, sizeof(int));
		read(fd[0], &sum, sizeof(int) * n);
		close(fd[1]);
		while(++i < n)
			sum_tot += sum[i];
		printf("\nSuma total = %d\n",sum_tot); 
		wait(NULL);

	}
}
