#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int pid;
	int err;

	pid = fork();
	if (pid == 0)
	{
		/*
		 * Creamos un texto para redirigir el resultado allí.
			Sol leer o crear si noe existe
			0777 -> El 0 es importante para decirle que es un número octal
			y no hexadecimal
			*/

		int file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (1);
		printf("The fd to printResults %d\n", file);
		int file2 = dup2(file, STDOUT_FILENO); //fd = 1
		if (file2 == -1)
			return (3);

		//Borramos el que hemos duplicado.
		printf("The duplicated fd %d\n", file2);
		close(file);
		err = execlp("ping", "ping", "-c", "1", "google.com", NULL); 
		if (err == -1)
		{
			printf("Could not fin program to execute!\n");
			return (2);
		}
		else
			printf("Aqui no llega porque se ha metido en el programa execlp\n");
	}
	else
	{
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			int exi = WIFEXITED(wstatus);
			printf("Exit %d\n", exi);
			int statusCode =  WEXITSTATUS(wstatus);
			if (statusCode == 0)
				printf("Sucess in Child %d\n", statusCode);
			else
				printf("Error: In child process %d\n", statusCode);
		}
	}
	return (0);
}
