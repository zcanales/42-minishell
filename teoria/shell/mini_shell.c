# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
#include <unistd.h>
#include <string.h>

//gcc -lreadline -L /sgoinfre/goinfre/Perso/zcanales/homebrew/opt/readline/lib -I /sgoinfre/goinfre/Perso/zcanales/homebrew/opt/readline/include mini_shell.c

char    *get_line(char *line)
{
    if (line) //Readline hace malloc asique hay que liberar memoria
    {
		free(line);
       line = NULL;
    }
    line = readline("\033[0;35m\033[1mPink 🥜 > \033[0m");
    if (line && line[0] != '\0' && !strcmp(line, "history -c")) //No queremos guardar comandos vacios com Ctrl + C
        add_history(line);
    return (line);
}

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
		rl_on_new_line(); //Para que aparezce Minishell otra vez prompt
//		rl_replace_line("", 0); // no aparece en el historial
		rl_redisplay(); //Aparece otra vez
    }

}

int main(void)
{
    char    *line;

	line = NULL;
    signal(SIGINT, sig_handler);
	while (1)
	{
//		sleep(2);
		line = get_line(line);
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (!strcmp(line, "exit")) //Ñapa
			break;
	//	free(line);
	}
	//system("leaks a.out");
	return (0);
}
/*
 *  int nb = getline(&buf, &size, stdin);
    if (nb == -1)
        printf("CTRL + D captured\n");
		*/
