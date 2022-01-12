/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:39:56 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/12 21:12:34 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//CLOSE_PIPES -> Bucle que cierra todas las pipes. 
//CHECK_QUOTES -> Cuando se encuentra comillas, avanza en string SIN PARAR hasta que encuentre otras iguales. 
//FREE_DOUBLE -> Libera un array doble
//IMPRIMIR -> Imprime struct. 

//CLOSE PIPES//

void close_pipes(t_shell *shell)
{
	int i;
    int j;
	
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

//CHECK_QUOTES//

void	check_quotes(char *s, int *index)
{
	int i;

	i = *index;
	if (s[i] == 34)
	{
		while (s[++i] && s[i] != 34)
			continue ;
	}
	else if (s[i] == 39)
	{
		while (s[++i] && s[i] != 39)
			continue ;
	}
	*index = i;
}

//FREE_DOUBLE//

void	free_double(char **s)
{
	int	i;

	i = -1;
//	while (s[++i])
//		free(s[i]);
	free(s);
}

//FREELIST///
void    ft_freelist(t_list **head)
{
    t_list  *temp;

    if (!*head)
        return ;
    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free (temp);
    }
	*head = NULL;
}


//IMPRIMIR//

void	imprimir(t_ch *ch)
{
	int i;

	i = -1;
	printf("		\033[0;31mINFO\033[0m\n");
    printf("	id child \033[0m == %d\n", ch->id_child);   //identificardor

    printf("	n infile == %d\n",ch->nbr_infile);
	while(++i < ch->nbr_infile)
    	printf("	   infile name  == %s / type = %d\n", ch->infile_t[i].file_name, ch->infile_t[i].type);
    
	i = -1;
	printf("	n outfile == %d\n",ch->nbr_outfile);
	while(++i < ch->nbr_outfile)
    	printf("	   outfile name  == %s - type = %d\n", ch->outfile_t[i].file_name, ch->outfile_t[i].type);
	printf("------\n");
	i = -1;
	while(ch->command_real[++i])
		printf("	comand real == %s\n",ch->command_real[i]);

	printf("		\033[0;31mEND\033[0m\n");


}
