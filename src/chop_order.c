/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chop_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/08 14:31:45 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//COUNT_PIQUITOS -> Numero de infiles y oufiles para hacer malloc de cada t_piquito
//CHOP_ORDER + CHOP_FILE_INFO -> Substrae del order los infiles
//GET_REAL_COMMAND -> Se queda con el comando LIMPIO y en un array. 

#include "../include/minishell.h"

void    count_piquitos(t_ch *ch, int *nbr_file, char c, t_piquito **file_t) 
{
	int i;
	char **file;
  
   	file = ft_split_2(ch->order, c, nbr_file);
	i = -1;
	free_double(file);
	(*file_t) = (t_piquito *)malloc(sizeof(t_piquito) * (*nbr_file));
	if (!(*file_t))
		exit(1);

}

void	chop_order(t_ch *ch)
{
    int i;

	i = 0;
    while (ch->order[i])
    {
		while (ch->order[i] == 32)
			i++;
		check_quotes(ch->order, &i);
        if (ch->order[i] ==  '<')// INFILES
			chop_file_info(ch, '<', '>', &i);
		else  if (ch->order[i] == '>') //OUTFILES
			chop_file_info(ch, '>', '<', &i);
        else //COMMAND
			ch->comando_bueno = get_real_command(ch, &i);
    }
}

void	chop_file_info(t_ch *ch, char c, char no_c, int *i)
{
	int type;
	int start;

	start = 0;
	type = 1;
	if  (ch->order[++*i] && ch->order[*i] ==  c)
	{
		type = 2;
		*i += 1;
	}
	while (ch->order[*i] && ch->order[*i] == 32) 	//Espacios
		*i += 1;
	start = *i;
	while (ch->order[*i] && ch->order[*i] != 32 && ch->order[*i] != no_c) 
		*i = *i +1;
	if (c == '<')
	{
		ch->infile_t[ch->index_in].file_name = ft_substr(ch->order, start, *i - start); 
		ch->infile_t[ch->index_in++].type = type;
	}
	else
	{
		ch->outfile_t[ch->index_out].file_name = ft_substr(ch->order, start, *i - start);
		ch->outfile_t[ch->index_out++].type = type;
	}
}

char	*get_real_command(t_ch *ch, int *i)
{
	int		start;
	char	*temp;
	char	*real_temp;

	start = *i;
	while (ch->order[*i] && ch->order[*i] != '<' && ch->order[*i] != '>')
		*i += 1;
	temp = ft_substr(ch->order, start, *i - start);
	if (!ch->comando_bueno)
		real_temp  = ft_strdup(temp);
	else
		real_temp = ft_strjoin(ch->comando_bueno,temp);
	free(temp);
	return (real_temp);
}
