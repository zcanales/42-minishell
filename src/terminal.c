/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:59:53 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/24 10:38:21 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
#include "../include/minishell.h"

char    *get_line(char *line)
{
    if (line) //Readline hace malloc asique hay que liberar memoria
    {
		free(line);
       line = NULL;
    }
    line = readline("\033[0;35m\033[1mPink 🥜 > \033[0m");
    if (line && line[0] != '\0') //No queremos guardar comandos vacios com Ctrl + C
        add_history(line);
	if (line && !ft_strncmp(line, "history -c", ft_strlen("history -c")))
		 rl_clear_history();	
    return (line);
}

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
		rl_on_new_line(); //Para que aparezce Minishell otra vez prompt
		rl_replace_line("", 0); // no aparece en el historial
		rl_redisplay(); //Aparece otra vez
    }

}

int create_terminal(void)
{
    char    *line;

	line = NULL;
	attributes();
    signal(SIGINT, sig_handler);
	while (1)
	{
		line = get_line(line);
		if (!line)
		{
			printf("exit\n");
			break;
		}
	}
	return (0);
}

