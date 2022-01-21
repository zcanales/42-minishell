/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/20 18:08:49 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	pre_chop_files(int *type, char c, int *i, char *order)
{
	char	no_c;

	if (c == '<')
		no_c = '>';
	else
		no_c = '<';
	if (order[++*i] && order[*i] == c)
	{
		*type = 2;
		*i += 1;
	}
	return (no_c);
}

void	chop_files(t_ch *ch, char c, int *i, char *order)
{
	int		type;
	int		start;
	char	no_c;

	type = 1;
	no_c = pre_chop_files(&type, c, i, order);
	while (order[*i] && order[*i] == 32)
		*i += 1;
	start = *i;
	while (order[*i] && order[*i] != 32 && order[*i] != no_c)
		*i = *i +1;
	if (c == '<')
	{
		ch->infile_t[ch->index_in].file_name
			= ft_substr(order, start, *i - start);
		ch->infile_t[ch->index_in++].type = type;
	}
	else
	{
		ch->outfile_t[ch->index_out].file_name
			= ft_substr(order, start, *i - start);
		ch->outfile_t[ch->index_out++].type = type;
	}
}

char	*chop_command(t_ch *ch, int *i, char *order)
{
	int		start;
	char	*temp;
	char	*real_temp;

	start = *i;
	real_temp = NULL;
	while (order[*i] && order[*i] != '<' && order[*i] != '>')
	{
		check_quotes(order, i);
		*i += 1;
	}
	temp = ft_substr(order, start, *i - start);
	if (!ch->command_group)
		real_temp = ft_strdup(temp);
	else
	{
		real_temp = ft_strjoin(ch->command_group, temp);
		free(ch->command_group);
	}
	free(temp);
	return (real_temp);
}

void	classify_order(t_ch *ch, char *order)
{
	int	i;

	i = 0;
	if (!order)
		return ;
	while (order[i])
	{
		while (order[i] && order[i] == 32)
			i++;
		if (order[i] && order[i] == '<')
			chop_files(ch, '<', &i, order);
		else if (order[i] && order[i] == '>')
			chop_files(ch, '>', &i, order);
		else
			ch->command_group = chop_command(ch, &i, order);
	}
}

void	get_child_info(t_shell *shell)
{
	int	i;

	i = -1;
	shell->my_pro->child = (t_ch *)ft_calloc(sizeof(t_ch),
			shell->my_pro->nbr_process);
	if (!shell->my_pro->child)
		status_error(strerror(errno), errno);
	while (++i < shell->my_pro->nbr_process)
	{
		count_peaks(&shell->my_pro->child[i].nbr_infile, '<',
			&shell->my_pro->child[i].infile_t, shell->my_pro->orders[i]);
		count_peaks(&shell->my_pro->child[i].nbr_outfile, '>',
			&shell->my_pro->child[i].outfile_t, shell->my_pro->orders[i]);
		classify_order(&shell->my_pro->child[i], shell->my_pro->orders[i]);
		shell->my_pro->child[i].command_split
			= ft_split_2(shell->my_pro->child[i].command_group,
				' ', &shell->my_pro->child[i].nbr_command);
		count_nbr_commands(&shell->my_pro->child[i]);
		clean_commands(shell, &shell->my_pro->child[i]);
		if (shell->my_pro->child[i].command_split
			&& shell->my_pro->nbr_process == 1)
			check_builtins_mother(&shell, i);
	}	
}
