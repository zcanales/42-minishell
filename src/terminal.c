/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:59:53 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/20 17:31:30 by eperaita         ###   ########.fr       */
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

void	attributes(t_shell *shell)
{
	if (tcgetattr(0, &shell->old) == -1)
		status_error(strerror(errno), errno);
	if (tcgetattr(0, &shell->changed) == -1)
		status_error(strerror(errno), errno);
	if (tcgetattr(0, &shell->child) == -1)
		status_error(strerror(errno), errno);
	shell->changed.c_lflag = shell->changed.c_lflag & ~ICANON & ECHO;
	shell->changed.c_cc[VQUIT] = 0;
	shell->child.c_lflag = shell->child.c_lflag & ECHO;
	if (tcsetattr(0, TCSANOW, &shell->changed) == -1)
		status_error(strerror(errno), errno);
}

void	free_and_init(t_shell *shell)
{
	int	a;
	int	i;

	a = -1;
	while (shell->my_pro->nbr_process > ++a)
	{
		free(shell->my_pro->fd[a]);
		i = -1;
		while (shell->my_pro->child->nbr_infile > ++i)
			free(shell->my_pro->child[a].infile_t[i].file_name);
		i = -1;
		while (shell->my_pro->child->nbr_outfile > ++i)
			free(shell->my_pro->child[a].outfile_t[i].file_name);
		free(shell->my_pro->child[a].outfile_t);
		free(shell->my_pro->child[a].infile_t);
		free(shell->my_pro->child[a].command_group);
		free_double(shell->my_pro->child[a].command_split, 2);
	}
	free(shell->my_pro->pid);
	free(shell->my_pro->fd[a]);
	free(shell->my_pro->fd);
	free(shell->my_pro->child);
	free_double(shell->my_pro->orders, 2);
	ft_memset(shell->my_pro, 0, sizeof(t_pro));
}

//PROMPT COMPLETO//
//	shell->line = readline("\033[0;35m\033[1mPink 🥜 > \033[0m");
char	*get_line(t_shell *shell)
{
	if (shell->line && shell->line[0] != '\0')
	{
		free(shell->line);
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
	if (g_mother == 0)
	{
		printf("\n");
		exit(0);
	}
}

int	create_terminal(t_shell *shell)
{
	g_mother = 1;
	shell->line = NULL;
	attributes(shell);
	signal(SIGINT, sig_handler);
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
			g_mother = 2;
			input(shell);
			free(shell->line);
			shell->line = NULL;
			tcsetattr(0, TCSANOW, &shell->changed);
			g_mother = 1;
		}
	}
	return (0);
}
