/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:30:38 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/22 18:20:19 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

//	CHILD PROCESS //
void	child_process(t_ch *child, t_shell *shell)
{
	is_redirected(shell->my_pro, child->id_child);
	re_pipe(shell, child->id_child);
	if (!child->command_split)
		exit(0);
	check_builtins_child(&shell, child->id_child);
	if (child->command_split[0] && (child->command_split[0][0] == '.'
		|| child->command_split[0][0] == '/'))
		child->command_split[0] = get_exe_path(shell, child->command_split[0]);
	g_mother = 0;
	exe_command(shell, child->id_child);
}

//MOTHER //
void	mother_process(t_shell *shell)
{
	int	i;
	int	status;
	int	pid;

	i = -1;
	while (++i < shell->my_pro->nbr_process)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == shell->my_pro->pid[shell->my_pro->nbr_process - 1])
				shell->status = WEXITSTATUS(status);
		if (pid == shell->my_pro->pid[shell->my_pro->nbr_process - 1]
			&& shell->my_pro->child[i].mom_builtin)
			shell->status = shell->status_builtin;
		if (i != shell->my_pro->nbr_process - 1)
			kill(shell->my_pro->pid[i + 1], SIGCONT);
	}
}

//CREATE PROCESSES//
void	create_processes(t_shell *shell)
{
	int	id;

	id = shell->my_pro->nbr_process;
	while (id--)
	{
		shell->my_pro->pid[id] = fork();
		if (shell->my_pro->pid[id] < 0)
			status_error(strerror(errno), errno);
		if (shell->my_pro->pid[id] != 0)
			kill(shell->my_pro->pid[id], SIGSTOP);
		else
		{	
			g_mother = 0;
			shell->my_pro->child[id].id_child = id;
			child_process(&shell->my_pro->child[id], shell);
		}
	}
	kill(shell->my_pro->pid[0], SIGCONT);
	close_pipes(shell);
	mother_process(shell);
}

//ALLOC PROCESSES//
int	alloc_processes(t_shell *shell)
{
	int	i;
	int	npipes;

	i = -1;
	shell->my_pro->orders = ft_split_2(shell->line,
			'|', &shell->my_pro->nbr_process);
	if (check_empty_pipe(shell->my_pro->orders))
		return (1);
	npipes = (shell->my_pro->nbr_process + 1);
	shell->my_pro->fd = (int **)malloc(npipes * sizeof(int *));
	while (++i < npipes)
	{
		shell->my_pro->fd[i] = (int *)malloc(2 * sizeof(int));
		if (!shell->my_pro->fd[i])
			status_error(strerror(errno), errno);
		if (pipe(shell->my_pro->fd[i]) < 0)
			status_error(strerror(errno), errno);
	}
	i = 0;
	shell->my_pro->pid = (int *)malloc(shell->my_pro->nbr_process
			* sizeof (int));
	if (shell->my_pro->pid < 0)
		status_error(strerror(errno), errno);
	get_child_info(shell);
	return (0);
}

//INPUT //
int	input(t_shell *shell)
{
	unlink("here_doc.txt");
	if (check_null_pipe(shell->line))
		return (1);
	if (check_error(shell->line))
	{
		shell->status = 258;
		return (1);
	}
	if (alloc_processes(shell))
	{
		shell->status = 258;
		free_double(shell->my_pro->orders, 2);
		return (1);
	}
	create_processes(shell);
	free_and_init(shell);
	return (0);
}
