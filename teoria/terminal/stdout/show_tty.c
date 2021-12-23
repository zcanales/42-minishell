#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	int fd = open("ioctl_prueba", O_RDONLY);
	int p[2];
	pipe(p);

	dup2(fd, 2);
	//Prueba 1
	//
	printf ("Terminal is %s\n" , ttyname(2)) ;
	//Prueba 2
	if (ttyname(2))
		printf ("Not redirected\n");
	else
		printf ("Is redirected\n");
	close(fd);
	return (0) ;
}

/*
 * Hacer 2 pruebass
 * 1 -> ./a.out
 * 2 -> ls | ./a.out
 * The problem is that in the second example, standard input was redirected, so le descriptor 0
was attached to a pipe instead.
 *
 * The ttyname() function returns the NULL string when there is
no terminal attached to the descriptor. The same thing will happen if you try calling it with le
descriptor 1 while standard output has been redirected. You can therefore use ttyname(0) as a test
for whether or not standard input or output is redirected , as in
*/





