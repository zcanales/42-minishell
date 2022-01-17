#include<stdio.h>
#include <string.h>
#include <errno.h>

// chdir function is declared
// inside this header
#include<unistd.h>
//https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
int main()
{
	char s[100];
	int error;

	// printing current working directory
	printf("%s\n", getcwd(s, 100));

	// using the command
	if (chdir("cd_1") != 0)
		printf("Pink: %s\n", strerror(errno));

	// printing current working directory
	printf("%s\n", getcwd(s, 100));

	// after chdir is executed
	return 0;
}
/*
#include <unistd.h>
#include <stdio.h>

// Main Method
int main() {

	char s[100];
// changing the current
// working directory(cwd)
// to /usr
if (chdir("borrar") != 0)
	perror("chdir() to /usr failed");
	printf("%s\n", getcwd(s, 100));

// changing the cwd to /tmp
if (chdir("/tmp") != 0)
	perror("chdir() to /temp failed");

// there is no /error
// directory in my pc
if (chdir("/error") != 0)

	// so chdir will return -1
	perror("chdir() to /error failed");

return 0;
}
*/

