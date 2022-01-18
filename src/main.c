/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:50:16 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/18 18:48:39 by zcanales         ###   ########.fr       */
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
 * 		2.1 ->INPUT -> analizar el comando que nos han pasado
 * 			"0"	CHECK_ERROR
 * 			"1" ALLOC_PROCESS
 * 			"2" CREATE_PROCESS
 * 		2.2 -> Una vez creada los PROCESS
 * 			MOTHER-->MOTHER_PROCESS
 * 			HIJO-->CHILD_PROCESS
 * 				"1" CHOP_ORDER
 * 					-Get infile/out
 * 				"2" REDIRECTION
 * 				"3" EXECUTE
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
