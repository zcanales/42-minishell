#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
	char inbuf ;
	char prompt [ ] =
				"Type any character follow by the 'Enter' key . "
				"Use Ctrl−D to exit \n";
	if (-1 == write(1 ,prompt , strlen(prompt)))
   	{
		write(1 ,"write failed \n", 13) ;
		exit(1);
	}
	while (read(0, &inbuf, 1) > 0)
		write(1 , &inbuf , 1);
	return (0);
}
