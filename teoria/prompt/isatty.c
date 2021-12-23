/*There is a function specically for testing whether a le descriptor is attached to a terminal or not
: -->>> ISATTY */

#include <stdio.h>
#include <unistd.h>
int main()
{
    //Prueba 2
    if (isatty(0))
        printf("%s\n", ttyname(0));
    else
        printf("not a terminal\n");
    return (0) ;
}

/*
 * If you run this program you will see something like
1-> ./a.out
	/dev/pts/1

and when input is redirected, you will see this:
2->  ls | ./a.out
not a terminal

When you are writing a program that expects the standard output device to be a terminal, you
can use either isatty() or ttyname() to check whether any standard stream has been redirected.
However, both of these functions can only be used with an open le, since they need a le descriptor,
and le descriptors exist only for open connections. I
*/
