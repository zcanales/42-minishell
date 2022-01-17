/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:30:38 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/17 20:15:32 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//INPUT -> Del input [shell->line] determina n* procesos [shell->my_pro->nbr_process]y splitea line en [shell->my_pro->orders]
//ALLOC_PROCESS -> aloja array de pipes, crea pipes y aloja array de pids de procesos.
//CREATE PROCESSES -> Fork * nbr_process -> redirige cada uno a CHILD_PROCESS
////CHILD PROCESS -> Ejecucion de hija
	//Contamos piquitos
	//Chop churro comando (chop_order.c)
	//Split real_comando (chop_order.c)
	//Redirecciones (exe.c)
	//Unlock siguiente hija
	//Exe (exe.c)
//MOTHER PROCESS -> Ejecucion de madre//
	
//imprimir(shell->my_pro->child);

#include "../include/minishell.h"
#include <signal.h>

//	CHILD PROCESS //

///OJO! Y si el comando es ./ ????
void	child_process(t_ch *child, t_shell *shell)
{
	/*HACER LAS REDIRECIONES */
	is_redirected(shell->my_pro, child->id_child);
	re_pipe(shell, child->id_child);	
	
	/*DESBLOQUEAR SIGUIENTE HIJA */
//	if (child->id_child != shell->my_pro->nbr_process - 1)
//		kill(shell->my_pro->pid[child->id_child], SIGCONT);

	 /*BUILTINGS*/
	if (!child->command_split)
		exit(0);
     check_builtins_child(&shell, child->id_child);

	 //expandir resto command_split[] cuales???? COMILLAS!!!
	
	/*EL ULTIMO PASO MANDAMOS A EJECUTAR */
	exe_command(shell, child->id_child);

}

//MOTHER //

void	mother_process(t_shell *shell)
{
	int i;
	int status;
	
	i = -1;
    while (++i < shell->my_pro->nbr_process)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			g_status = WEXITSTATUS(status);
			printf("Hijo %d en problemas\n", i);
		}
		else 
			g_status = 0;
		if (i != shell->my_pro->nbr_process - 1)
			kill(shell->my_pro->pid[i + 1], SIGCONT);
	}
	printf("status --> %d\n", g_status);
	//unlink("here_doc.txt");
	//printf("Process OK\n");
}

//CREATE PROCESSES//

void create_processes(t_shell *shell)
{
	int id;

	id = shell->my_pro->nbr_process;
    while (id--)
    {
        shell->my_pro->pid[id] = fork();
        if (shell->my_pro->pid[id] < 0)
			perror("Error");
		if (shell->my_pro->pid[id] != 0)
			kill(shell->my_pro->pid[id], SIGSTOP);
		else
		{	
			shell->my_pro->child[id].id_child = id;
			child_process(&shell->my_pro->child[id], shell);
		}
    }
	kill(shell->my_pro->pid[0], SIGCONT);
	close_pipes(shell); //Hay que cerrar todas las pipes(bucle)
	mother_process(shell);
}

//ALLOC PROCESSES//

void alloc_processes(t_shell *shell)
{
    int i;
    int npipes;

    i = -1;
    shell->my_pro->orders = ft_split_2(shell->line, '|', &shell->my_pro->nbr_process);	//split del input con pipes
	check_error_pipe(shell->my_pro->orders);
    npipes = (shell->my_pro->nbr_process + 1);
    shell->my_pro->fd = (int **)malloc(npipes * sizeof(int *)); //alojo array de pipes
    if (!shell->my_pro->fd)
        exit(1);
    while (++i < npipes)
    {
        shell->my_pro->fd[i] = (int *)malloc(2 * sizeof(int)); //alojo cada pipe
        if (!shell->my_pro->fd[i])
            exit(1);
        if (pipe(shell->my_pro->fd[i]) < 0)      //creo la pipe
        {
            printf("Error pipe\n");
            exit(1);
        }
    }
    i = 0;
    shell->my_pro->pid = (int *)malloc(shell->my_pro->nbr_process * sizeof (int)); //alojo array de hijos
    if (shell->my_pro->pid < 0)
        exit(1);
	get_child_info(shell);
}

//INPUT //

int input(t_shell *shell)
{
    /*if (shell->line[0] == '|') //  ERROR completar. Ej: Que no nos hayan metido solo |, <<< ...
        exit (1);*/
/*	int i =-1;
	printf("--------------PADRE-----------------\n");
	while (shell->my_env->env[++i])
		printf("new_env= %s\n",shell->my_env->env[i]);
	printf("-------------------------------\n");*/
	unlink("here_doc.txt");
	check_error(shell->line);
    alloc_processes(shell);
    create_processes(shell);
    return (0);
}
