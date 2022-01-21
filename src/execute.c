/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/21 20:51:09 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>
#include <signal.h>

//CLOSE PIPES//
void	close_pipes(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->my_pro->nbr_process + 1)
	{
		j = 0;
		while (j < 2)
		{
			close(shell->my_pro->fd[i][j]);
			j++;
		}
		i++;
	}
}

//IS_REDIRECTED//
void	is_redirected(t_pro *pro, int id)
{
	int	i;

	i = -1;
	while (++i < pro->child[id].nbr_infile)
	{
		if (i == 0)
			unlink("here_doc.txt");
		if (pro->child[id].infile_t[i].type == 2)
		{
			here_doc(pro, i, id);
			if (i != (pro->child[id].nbr_infile - 1))
				unlink("here_doc.txt");
		}
		else
			re_in_out(pro, 0, i, id);
	}
	i = -1;
	while (++i < pro->child[id].nbr_outfile)
		re_in_out(pro, 1, i, id);
}

//RE_IN_OUT  
void	re_in_out(t_pro *pro, int in_out, int index, int id)
{
	if (in_out == 0)
	{
		pro->fd[id][0] = open(pro->child[id].infile_t[index].file_name,
				O_RDONLY);
		if (pro->fd[id][0] < 0)
			status_error(strerror(errno), errno);
	}
	if (in_out == 1)
	{
		if (pro->child[id].outfile_t[index].type == 1)
			pro->fd[id + 1][1] = open(pro->child[id].outfile_t[index].file_name,
					O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (pro->child[id].outfile_t[index].type == 2)
			pro->fd[id + 1][1] = open(pro->child[id].outfile_t[index].file_name,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		if (pro->fd[id + 1][1] < 0)
			status_error(strerror(errno), errno);
	}
}

//RE_PIPE//
void	re_pipe(t_shell *shell, int id)
{
	if (id != 0 || (id == 0 && shell->my_pro->child[id].nbr_infile))
		dup2(shell->my_pro->fd[id][0], 0);
	if (id != shell->my_pro->nbr_process - 1)
		dup2(shell->my_pro->fd[id + 1][1], 1);
	else if (id == shell->my_pro->nbr_process - 1
		&& shell->my_pro->child[id].nbr_outfile)
		dup2(shell->my_pro->fd[id + 1][1], 1);
	close_pipes(shell);
}

//EXE//
void	exe_command(t_shell *shell, int id)
{
	int		i;
	char	*temp_access;

	if (!shell->my_pro->child[id].command_split[0])
		exit(0);
	i = -1;
	while (shell->my_env->paths[++i])
	{
		temp_access = ft_strjoin(shell->my_env->paths[i],
				shell->my_pro->child[id].command_split[0]);
		if (!access(temp_access, X_OK))
		{
			execve(ft_strjoin(shell->my_env->paths[i],
					shell->my_pro->child[id].command_split[0]),
				shell->my_pro->child[id].command_split,
				shell->my_env->env);
		}
		free(temp_access);
	}
	printf_error(shell->my_pro->child[id].command_split[0], 2, shell);
	exit(127);
}
