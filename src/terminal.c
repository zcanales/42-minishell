/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:59:53 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/27 14:15:38 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
#include "../include/minishell.h"

void	free_and_init(t_shell *shell)
{
	int i;

	i = -1;
	while (shell->my_pro->commands[++i])
		free(shell->my_pro->commands[i]);
	free(shell->my_pro->commands);
	free(shell->line);
	shell->line = NULL;
	ft_memset(shell->my_pro, 0, sizeof(t_pro));

}

char    *get_line(t_shell *shell)
{
    if (shell->line) //Readline hace malloc asique hay que liberar memoria
    {
		//free_line
		////free_commands
		//inicializar variables
		free_and_init(shell);
      // shell->line = NULL;
    }
    shell->line = readline("\033[0;35m\033[1mPink 🥜 > \033[0m");
    if (shell->line && shell->line[0] != '\0') //No queremos guardar comandos vacios com Ctrl + C
        add_history(shell->line);
	if (shell->line && !ft_strncmp(shell->line, "history -c", ft_strlen("history -c")))
		 rl_clear_history();	
    return (shell->line);
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

int create_terminal(t_shell *shell)
{

	shell->line = NULL;
	attributes(shell);
    signal(SIGINT, sig_handler);
	while (1)
	{
		shell->line = get_line(shell);
		if (!shell->line)
		{
			printf("exit\n");
			break;
		}
		else
			input(shell);
	}
	return (0);
}

