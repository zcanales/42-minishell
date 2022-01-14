/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:39:56 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/14 14:13:07 by zcanales         ###   ########.fr       */
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

int	check_quotes(char *s, int *index)
{
	int i;
	int equal;

	i = *index;
	equal = 0;
	if (s[i] == 34)
	{
		while (s[++i] && s[i] != 34)
		{
			if (s[i] == '=')
				equal = 1;
		}
	}
	else if (s[i] == 39)
	{
		while (s[++i] && s[i] != 39)
		{
			if (s[i] == '=')
				equal = 1;
		}
	}
	*index = i;
	return (equal);
}

//FT_SUB_JOIN
char *ft_substr_strjoin(char *to_sub, char *to_join, int start, int end)
{
    char    *real_temp;
    char    *temp;

    temp = ft_substr(to_sub, start, end - start);
    if (!to_join)
        real_temp  = ft_strdup(temp);
    else
    {
        real_temp = ft_strjoin(to_join, temp);
        free(to_join);
    }
    free(temp);
    return (real_temp);
}
//FREE_DOUBLE//

void	free_double(char **s, int check)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	if (check == 2)
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
	while(ch->command_split[++i])
		printf("	comand real == %s\n",ch->command_split[i]);

	printf("		\033[0;31mEND\033[0m\n");


}
