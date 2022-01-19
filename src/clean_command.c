/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:04:43 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/19 11:40:10 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void count_nbr_commands(t_ch *child)
{
	int a;
		
	a = -1;
	child->nbr_command = 0;
	while (child->command_split[++a])
		child->nbr_command++;
}

void clean_commands(t_shell *shell, t_ch *child)
{
	int a;

	if (child->command_split)
		child->command_split = fill_quote_dollar(child->command_split,
				shell, child->nbr_command, 2);
	a= -1;
	while(++a < child->nbr_infile)
	{
		child->infile_t[a].file_name_clean
			= fill_quote_dollar(&child->infile_t[a].file_name,
					shell, child->nbr_infile, 1);
		child->infile_t[a].file_name
			= convert_array_to_string(child->infile_t[a].file_name_clean);
	}
	a= -1;
	while(++a < child->nbr_outfile)
	{
		child->outfile_t[a].file_name_clean
			= fill_quote_dollar(&child->outfile_t[a].file_name,
					shell, child->nbr_outfile, 1);
		child->outfile_t[a].file_name
			= convert_array_to_string(child->outfile_t[a].file_name_clean);
	}
}


