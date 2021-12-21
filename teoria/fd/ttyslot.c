/*
 * #define _XOPEN_SOURCE_EXTENDED 1
#include <stdlib.h>

int ttyslot(void);

The ttyslot() function returns the index of the current user's entry in the utmpx database. The current user's entry is an entry for which the ut_line member matches the name of a terminal device associated with any of the process's file descriptors 0, 1 or 2. The ttyname() function is used to obtain the terminal device. The "/dev/" part returned by ttyname() is not used when searching the utmpx database member ut_line.

utmpx = on Unix-like systems that keep track of all logins and logouts to the system.

*
*/
//#define _XOPEN_SOURCE_EXTENDED 1
//#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{

	int err = ttyslot();
	printf("err =%d\n", err);
	return (0);

}
