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
		//En el scrip no sabe que es el |
		int err = execlp("ping", "ping", "-c", "1", "google.com", "|", "grep", "\"rtt\"", NULL); 
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
