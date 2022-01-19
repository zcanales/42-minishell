/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:59:53 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/19 19:36:35 by eperaita         ###   ########.fr       */
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
	free(shell->line);
	shell->line = NULL;
	ft_memset(shell->my_pro, 0, sizeof(t_pro));
	ft_memset(shell->my_pro->child, 0, sizeof(t_ch));
}

char	*get_line(t_shell *shell)
{
	if (shell->line && shell->line[0] != '\0')
		free_and_init(shell);
	shell->line = readline("\033[0;35m\033[1mPink 🥜 > \033[0m");
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
			break ;
		}
		else if (shell->line[0] != '\0')
		{
			g_mother = 2;
			input(shell);
			tcsetattr(0, TCSANOW, &shell->changed);
			g_mother = 1;
			free_and_init(shell);
		}
	}
	return (0);
}
