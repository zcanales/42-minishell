/* CELEBI03

   This example determines if a file descriptor is
   associated with a terminal.

 */
#define _POSIX_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void check_fd(int fd) {
  printf("fd %d is ", fd);
  if (!isatty(fd))
    printf("NOT a tty\n");
  else
    printf("a tty\n");
}

int main()
{
  int p[2], fd;
  char fn[]="temp.file";

  if (pipe(p) != 0)
    perror("pipe() error");
  else 
  {
    if ((fd = creat(fn, S_IWUSR)) < 0)
      perror("creat() error");
    else 
	{
      check_fd(0);
      check_fd(fileno(stderr));
      check_fd(p[1]);
      check_fd(fd);
      close(fd);
      unlink(fn);
    }
    close(p[0]);
    close(p[1]);
  }
  int fd_2 = open("prueba", O_RDONLY);
  check_fd(fd_2);
  close(fd_2);
}
