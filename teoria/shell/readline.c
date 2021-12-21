#include <string.h> 	//strmcmp

/* Standard include files. stdio.h is required. */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

/* Used for select(2) */
#include <sys/types.h>
#include <sys/select.h>
#include <signal.h>
#include <stdio.h>

/* Standard readline include files. */
#include <readline/readline.h>
#include <readline/history.h>

/* ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
 * * IMPORTANTEEEEEEE 
 * Compilar con = -lreadline 
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * */
int main(void)
{
	printf("Para salir escribir: 'exit'\n");
    while (1)
    {
        char * str = readline("Myshell $");
		printf("Copia: %s\n", str);
	rl_on_new_line();
		if (!(strncmp(str, "exit", 4)))
   		{
			free(str);
			break;
		}
		free(str);
    }
	//rl_clear_history();
}
