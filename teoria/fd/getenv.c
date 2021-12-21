/*
 *  #include <stdlib.h>

       char *getenv(const char *name);
	    The getenv() function searches the environment list to find the
       environment variable name, and returns a pointer to the
       corresponding value string.

	   The getenv() function returns a pointer to the value in the
       environment, or NULL if there is no match.
	   */

/* CELEBG05

   In this example, *pathvar points to the value of the PATH
   environment variable.
   In a POSIX environment, this variable would be from the CENV
   group ID.

   Si ponemos env en la terminal aparece toda la información
 */
#include <stdlib.h>
#include <stdio.h>

/*
 * OPCION 1
int main()
{
   char *value;

   value = getenv("PATH");
   printf("PATH = %s\n", value);
   value = getenv("USER");
   printf("USER = %s\n", value);
   value = getenv("PASSWORD");
   printf("PASSWORe	 = %s\n", value);
   return (0);
}*/

/*
 * OPCION 2
int main(int argc, char **argv, char **envp)
{

   for (int i = 0; envp[i] != NULL; i++)
	   printf("%d : %s\n", i, envp[i]);
   return (0);
}
*/
 OPCION 3
extern char **environ;

int main(int argc, char **argv, char **envp)
{

   for (int i = 0; environ[i] != NULL; i++)
       printf("%d : %s\n", i, environ[i]);
   return (0);
}


//OPCION 4 -> Poner en la terminal
//PASSCODE=HereThereBeMonster ./a.out
//Export PASSCODE=ThereThereBeMonster ./a.out
//
//Para quitar -> unset PASSCODE

