#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>

struct termios vieja;
struct sigaction int_old;
int dev=11;

void aborto (int);

int main (void) {
  char username[33];
  char	password[33];
	struct termios vieja;
	struct termios actual;
	FILE *fd;

	if ((fd = fopen(ctermid(NULL) ,"r+")) == NULL)
		return (1);
	printf("login : ");
	fgets(username, 32, fd);

	/*Now turn off echo */
  if (tcgetattr(0, &vieja)==-1) {
    perror ("ioctl/TCGETA vieja:");
    return 10;
  }
  if (tcgetattr(0, &actual)==-1) {
    perror ("ioctl/TCGETA actual:");
    return 10;
  }
	actual.c_lflag=actual.c_lflag & ~ ECHO; // ~ICANON | ECHO;i
	if (tcsetattr(0,TCSANOW, &actual)==-1) {
    perror ("ioctl/TCSETA actual:");
  }
	printf("password: ");
	fgets(password, 32, fd);

	tcsetattr(0,TCSANOW, &vieja);
	printf("\n");

  return (0);
}
