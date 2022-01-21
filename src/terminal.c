/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:59:53 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/21 20:51:07 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "../include/minishell.h"

void	ft_free(void *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
}

void	free_and_init(t_shell *shell)
{
	int	a;
	int	i;

	a = -1;
	while (++a < shell->my_pro->nbr_process)
	{
		ft_free(shell->my_pro->fd[a]);
		i = -1;
		while (++i < shell->my_pro->child[a].nbr_infile)
			ft_free(shell->my_pro->child[a].infile_t[i].file_name);
		i = -1;
		while (++i < shell->my_pro->child[a].nbr_outfile)
			ft_free(shell->my_pro->child[a].outfile_t[i].file_name);
		ft_free(shell->my_pro->child[a].outfile_t);
		ft_free(shell->my_pro->child[a].infile_t);
		ft_free(shell->my_pro->child[a].command_group);
		free_double(shell->my_pro->child[a].command_split, 2);
	}
	ft_free(shell->my_pro->pid);
	ft_free(shell->my_pro->fd[a]);
	ft_free(shell->my_pro->fd);
	ft_free(shell->my_pro->child);
	free_double(shell->my_pro->orders, 2);
	ft_memset(shell->my_pro, 0, sizeof(t_pro));
}

//PROMPT COMPLETO//
//	shell->line = readline("\033[0;35m\033[1mPink 🥜 > \033[0m");
char	*get_line(t_shell *shell)
{
	if (shell->line && shell->line[0] != '\0')
	{
		ft_free(shell->line);
		shell->line = NULL;
	}
	shell->line = readline("Pink Peanuts > ");
	if (shell->line && shell->line[0] != '\0')
		add_history(shell->line);
	if (shell->line && !ft_strncmp(shell->line, "history -c",
			ft_strlen("history -c")))
		rl_clear_history();
	return (shell->line);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT && g_mother == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGINT && g_mother == 0)
	{
		printf("\n");
		rl_on_new_line();
	//	exit(0);
	}
	if (signum == SIGQUIT && g_mother == 0)
		printf("^Quit : 3\n");
}

int	create_terminal(t_shell *shell)
{
	g_mother = 1;
	shell->line = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		shell->line = get_line(shell);
		if (!shell->line)
		{
			printf("exit\n");
			exit(0);
		}
		else if (shell->line[0] != '\0')
		{
			input(shell);
			ft_free(shell->line);
			shell->line = NULL;
			g_mother = 1;
		}
	}
	return (0);
}
