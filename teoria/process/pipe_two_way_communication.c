#include <stdio.h>	/*	printf , scanf */
#include <unistd.h>	/* write, read, close, fork, pipe*/
#include <time.h>	/*time*/
#include <stdlib.h>	/*rand	*/
/*Enviar inforacion entre processos. Así no se copia toda la info cuando se hae fork*/

int err(char *str, int err)
{
	if (str)
		printf("%s\n", str);
	return (err);
}

/* We cannot have a pipe that receive 
 * data and write in the same process,
 *  we have to have 2 pipes */

//BAD PRACTICE
/*int main(int argc, char **argV)
{
	int p1[2];
	if (pipe(p1) == -1)
		return (err("Error: Pipe", 1));
	int id = fork();
	if (id == -1)
		return (err("Error: Fork", 2));
	if (id == 0)
	{
		int x;
		if (read(p1[0], &x, sizeof(x)) == -1)
			return (err("Error: Reading", 3));
		printf("Got from child process %d\n", x);
		x *= 4;
		if (write(p1[1], &x, sizeof(x)) == -1)
			return (err("Error: Writing", 4));
		printf("Wrote Child %d\n", x);

	}
	else
	{
		srand(time(NULL));
		int y = rand() % 10;
		if (write(p1[1], &y, sizeof(y)) == -1)
			return (err("Error: Writing", 5));
		printf("Wrote Mother %d\n", y);
		if (read(p1[0], &y, sizeof(int)) == -1)
			return (err("Error: Reading", 4));
		printf("Result = %d\n", y);
	}
		close(p1[0]);
		close(p1[1]);
	return (0);
}*/

//GOOD PRACTICE
int main(int argc, char **argV)
{
    int p1[2]; //Child -> Mother
	int p2[2]; //Mother -> Child
    if (pipe(p1) == -1 || pipe(p2) == -1)
        return (err("Error: Pipe", 1));
    int id = fork();
    if (id == -1)
        return (err("Error: Fork", 2));
    if (id == 0)
    {
		close(p2[1]);
		close(p1[0]);
        int x;
        if (read(p2[0], &x, sizeof(x)) == -1)
            return (err("Error: Reading", 3));
        printf("Got from child process %d\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1)
            return (err("Error: Writing", 4));
        printf("Wrote Child %d\n", x);
        close(p1[1]);
        close(p2[0]);

    }
    else
    {
		close(p1[1]);
		close(p2[0]);
        srand(time(NULL));
        int y = rand() % 10;
        if (write(p2[1], &y, sizeof(y)) == -1)
            return (err("Error: Writing", 5));
        printf("Wrote Mother %d\n", y);
        if (read(p1[0], &y, sizeof(int)) == -1)
            return (err("Error: Reading", 4));
        printf("Result = %d\n", y);
        close(p1[0]);
        close(p2[1]);
    }
    return (0);
}
