/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:00:08 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/27 17:30:44 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	Esto es para mas adelante */
void	ft_sort_builtins(t_shell *shell)
{
	if (!(ft_strncmp(comand, "echo", ft_strlen("echo"))))
		ft_echo(shell);
	if (!(ft_strncmp(comand, "cd", ft_strlen("cd"))))
		ft_pwd(shell);
	if (!(ft_strncmp(comand, "pwd", ft_strlen("pwd"))))
		ft_echo(shell);
}
