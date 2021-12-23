#include <unistd.h>
#include <ctype.h>

/* stty -icanon ; ./transpose*/
int main (int argc ,char *argv [ ] )
{
	char ch ;
	while (read (0 , &ch , 1) > 0 )
  	{
//		if (islower(ch))
//			ch ='a' + 'z' - ch;
		write (1 , &ch , 1);
	}
	return (0);
}
