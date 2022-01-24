/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:59:53 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/24 14:16:30 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "../include/minishell.h"

//CREATE_TERMINAL -> while (1) loop. 
	//SIG_HANDLER -> Sets signals ^D / ^C / ^\ (mom or ch with global g_mother)
	//GET_LINE -> Prints the prompt, addhistory
	//(processes.c)
//FREE_AND_INIT -> Frees data for the new input line
	//FT_FREE -> Make sure if exist data and free

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
/*	if (signum == SIGINT && g_mother == 4)
	{
		printf("\n");
		rl_on_new_line();
	}*/
//	if (signum == SIGQUIT && g_mother == 4)
//		write(1, "Quit : 3\n", 9);
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
			g_mother = 4;
			input(shell);
			ft_free(shell->line);
			shell->line = NULL;
			g_mother = 1;
		}
	}
	return (0);
}
