/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:34:05 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/24 12:30:48 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <fcntl.h>
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

static void	ft_get_env(char **env, t_args *com)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	com->env = env;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			path = env[i];
		i++;
	}
	path = path + 5;
	com->env_paths = ft_split(path, ':');
	i = 0;
	while (com->env_paths[i])
	{
		temp = ft_strjoin(com->env_paths[i], "/");
		free(com->env_paths[i]);
		com->env_paths[i] = temp;
		i++;
	}
}

static void	ft_exe(char *order, t_args *com, int child)
{
	int		i;
	char	*temp_access;

	i = 0;
	com->commands = ft_split(order, ' ');
	while (com->env_paths[i])
	{
		temp_access = ft_strjoin(com->env_paths[i], com->commands[0]);
		if (!access(temp_access, X_OK))
		{
			dup2(com->fd[child][0], 0);
			dup2(com->fd[child + 1][1], 1);
			ft_close(com);
			if (execve(ft_strjoin(com->env_paths[i],
						com->commands[0]), com->commands, com->env) < 0)
				ft_error(com);
		}
		free(temp_access);
		free(com->env_paths[i]);
		i++;
	}
	free(com->pid);
	ft_error(com);
}

static void	ft_alloc(t_args *com)
{
	int	i;

	i = 0;
	com->fd = (int **)malloc(com->npipes * sizeof(int *));
	while (i < com->npipes)
	{
		com->fd[i] = (int *)malloc(2 * sizeof(int));
		if (!com->fd)
			ft_error(com);
		if (pipe(com->fd[i]) < 0)
			ft_error(com);
		i++;
	}
	i = 0;
	com->pid = (int *)malloc(com->nchild * sizeof (int));
	if (com->pid < 0)
	{
		free(com->pid);
		ft_error (com);
	}
}

static void	ft_re_in_out(int argc, char **argv, t_args *com)
{
	com->fd[0][0] = open(argv[1], O_RDONLY);
	if (com->fd[0][0] < 0)
		exit (1);
	com->fd[com->nchild][1] = open(argv[argc - 1],
			O_RDWR | O_TRUNC | O_CREAT, 0755);
	if (com->fd[com->nchild][1] < 0)
		exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_args	com;
	int		i;

	i = 0;
	if (argc != 5)
		exit (1);
	com.nchild = argc - 3;
	com.npipes = com.nchild + 1;
	ft_get_env(env, &com);
	ft_alloc(&com);
	ft_re_in_out(argc, argv, &com);
	while (i < com.nchild)
	{
		com.pid[i] = fork();
		if (com.pid[i] < 0)
			perror("Error");
		if (com.pid[i] == 0)
			ft_exe(argv[i + 2], &com, i);
		i++;
	}
	ft_free_pipes(&com);
	free(com.pid);
	return (0);
}
