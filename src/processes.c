/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:30:38 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/19 12:36:05 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

///////////////// -  "./" -  //////////////////
char	*get_exe_path(t_shell *shell, char *command_split)
{
	char	*new_command;

	free_double(shell->my_env->paths, 2);
	shell->my_env->paths = (char **)ft_calloc(sizeof(char *), 2);
	if (!shell->my_env->paths)
		status_error(strerror(errno), errno);
	shell->my_env->paths[0] = ft_substr(command_split, 0,
			ft_strlen(command_split)
			- ft_strlen(ft_strrchr(command_split, '/')) + 1);
	new_command = ft_strdup(ft_strrchr(command_split, '/') + 1);
	free (command_split);
	return (new_command);
}

//	CHILD PROCESS //
void	child_process(t_ch *child, t_shell *shell)
{
	tcsetattr(0, TCSANOW, &shell->child);
	is_redirected(shell->my_pro, child->id_child);
	re_pipe(shell, child->id_child);
	tcsetattr(0, TCSANOW, &shell->old);
	if (child->id_child != shell->my_pro->nbr_process - 1)
		kill(shell->my_pro->pid[child->id_child], SIGCONT);
	if (!child->command_split)
		status_error(strerror(errno), errno);
	check_builtins_child(&shell, child->id_child);
	if (child->command_split[0] && (child->command_split[0][0] == '.'
		|| child->command_split[0][0] == '/'))
		child->command_split[0] = get_exe_path(shell, child->command_split[0]);
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
			tcsetattr(0, TCSANOW, &shell->old);
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
	if (check_error_pipe(shell->my_pro->orders))
		return (1);
	npipes = (shell->my_pro->nbr_process + 1);
	shell->my_pro->fd = (int **)malloc(npipes * sizeof(int *));
	if (!shell->my_pro->fd)
		status_error(strerror(errno), errno);
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
	if (check_error(shell->line))
		return (1);
	if (alloc_processes(shell))
		return (1);
	create_processes(shell);
	return (0);
}
