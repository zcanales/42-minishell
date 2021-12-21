#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char **argv)
{
	int pid;
	int err;

	pid = fork();
	if (pid == 0)
	{
		//google.coN no existe-> tiene que dar error
		err = execlp("ping", "ping", "-c", "1", "google.con", NULL); 
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
		//Hay que mirar si el exit del child da error o no.
		//Si ponemos solo wait(NULL); va a ejecutar el "Sucess"
		int wstatus;
		wait(&wstatus);
		//wait(NULL);
		//WIFEXITED
		//returns true if the child terminated normally, that is, by
		//calling exit(3) or _exit(2), or by returning from main()
//		if (status != 0)
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
