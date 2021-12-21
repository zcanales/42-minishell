/* CELEBU06

   This example removes a directory entry, using unlink().
   #define _POSIX_SOURCE
	#include <unistd.h>

	int unlink(const char *pathname);

	If successful, unlink() returns 0.

	If unsuccessful, unlink() returns -1 and sets errno to one of the follow	ing values:
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  int fd;
  char fn[]="borrar";

  if ((fd = creat(fn, S_IWUSR)) < 0)
    perror("creat() error");
  else {
	  sleep(3);
    close(fd);
    if (unlink(fn) != 0)
      perror("unlink() error");
	else
		printf("file unlinked\n");
  }
}
