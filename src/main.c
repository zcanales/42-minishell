/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:50:16 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/03 20:34:16 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

/*
 * 1. PASO = INIT -> 
 * 		-crear la estructura
 * 		-inicializarla a 0 
 * 		-crear el environment (GET_ENVIRONMENT)
 * 2. PASO = CREATE_TERMINAL ->
 * 		-crear la terminal
 * 		2.1 ->INPUT -> analizar el comando que nos han pasado
 * 		-nbr_process (ft_split_2)
 * 		2.2 ->
 *
 * 		*/

int main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	(void)argc;
	(void)argv;
	init(&shell, env);
	create_terminal(shell);
	return (0);
}
