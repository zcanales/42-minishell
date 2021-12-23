/*
	#define _POSIX_SOURCE
	#include <unistd.h>

	char *ttyname(int fildes);
	*/

/* CELEBT16

   This example provides the pathname of the terminal
   associated with stdin.

 */

#define _POSIX_SOURCE
#include <unistd.h>		//ttyname
#include <stdio.h>
#include <string.h>

int main() {
  char *ret, tty[40];

  if ((ret = ttyname(STDIN_FILENO)) == NULL)
    perror("ttyname() error");
  else 
  {
    strcpy(tty, ret);
    printf("The ttyname associated with my stdin is %s\n", tty);
  }
}
