#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	/*
	execl("C: \\Windows\\System32\\ping.exe", "C: \\Windows\\System32\\ping.exe", "google.com", NULL);*/
	execlp("ping", "ping", "-c", "3", "google.com", NULL);
	printf("Success!");
	return (0);
}

/*  int
     execve(const char *path, char *const argv[], char *const envp[])
	 path = direccion del ejecutable
	 argv[0] = ejecutable
	 argv[1..] = parametros
	 argv[ultimo] = ultimo parametro = NULL
	 */
/*
 int
     execl(const char *path, const char *arg0, ... , (char *)0 );
	 */
/*
 * int
     execlp(const char *file, const char *arg0, ... , (char *)0 *;
*/
