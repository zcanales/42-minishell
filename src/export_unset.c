/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:59:12 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/21 20:51:11 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int filter_unset(char *var)
{
	int a;
	
	a = -1;
	while (var[++a])
	{
		if (!ft_isalnum(var[a]) && var[a] != '_')
		{
			printf("Pink peanuts: %s not a valid identifier\n", var);
			return (1);
		}
	}
	return (0);
}

void	create_lists(t_shell *shell, int replace)
{
	int	i;

	i = -1;
	while (shell->my_pro->nbr_process == 1 && shell->my_env->env[++i])
	{
		ft_lstadd_back(&shell->my_env->list_env,
			ft_lstnew(shell->my_env->env[i]));
	}
	i = -1;
	while (shell->my_env->var_real[++i])
	{
		if (shell->my_env->var_real[i][0] != '='
				&& (ft_isalpha(shell->my_env->var_real[i][0])
					|| shell->my_env->var_real[i][0] == '_'))
		{
			if ((replace != 0 || (replace == 0
					&& !filter_unset(shell->my_env->var_real[i])))
					&& shell->my_pro->nbr_process == 1)
				ft_lstadd_back(&shell->my_env->list_var_real,
					ft_lstnew(shell->my_env->var_real[i]));
		}
		else
			printf_error(shell->my_env->var_real[i], 1, shell);

	}
}

int	replace_first(t_list **head_env, t_list *temp_var, int replace)
{
	t_list	*temp;
	t_list	*to_free;

	temp = *head_env;
	to_free = *head_env;
	if (ft_strcmp_len((char *)temp->content,
			(char *)temp_var->content))
	{
		if (replace != 0)
		{
			temp = temp->next;
			(*head_env) = ft_lstnew((char *)temp_var->content);
			(*head_env)->next = temp;
		}
		else
			(*head_env) = temp->next;
		free(to_free);
		return (1);
	}
	return (0);
}

int	replace_repeated(t_list **head_env, t_list *temp_var, int replace)
{
	t_list	*temp_back;
	t_list	*temp_env;

	if (replace_first(head_env, temp_var, replace))
		return (0);
	temp_back = *head_env;
	temp_env = temp_back->next;
	while (temp_env)
	{
		if (ft_strcmp_len((char *)temp_env->content, (char *)temp_var->content))
		{
			if (replace != 0)
			{
				temp_back->next = ft_lstnew((char *)temp_var->content);
				temp_back->next->next = temp_env->next;
			}
			else
				temp_back->next = temp_env->next;
			free(temp_env);
			return (0);
		}
		temp_back = temp_back->next;
		temp_env = temp_back->next;
	}
	return (1);
}	

void	replace_env(t_shell *shell, int replace)
{
	t_list	*temp_var;

	temp_var = shell->my_env->list_var_real;
	while (temp_var)
	{
		if (replace_repeated(&shell->my_env->list_env,
				temp_var, replace) && replace != 0)
			ft_lstadd_back(&shell->my_env->list_env,
				ft_lstnew((char *)temp_var->content));
		temp_var = temp_var->next;
	}
}

char	**convert_list_array(t_shell **shell)
{
	char	**temp_env;
	t_list	*temp;
	int		i;

	i = -1;
	temp = (*shell)->my_env->list_env;
	(*shell)->my_env->nbr_env = ft_lstsize(temp);
	temp_env = (char **)malloc(sizeof(char *)
			* ((*shell)->my_env->nbr_env + 1));
	if (!temp_env)
		status_error(strerror(errno), errno);
	while (temp)
	{
		temp_env[++i] = ft_strdup((char *)temp->content);
		temp = temp->next;
	}
	temp_env[(*shell)->my_env->nbr_env] = NULL;
	ft_freelist(&(*shell)->my_env->list_env);
	free_double((*shell)->my_env->env, 2);
	(*shell)->my_env->env = NULL;
	return (temp_env);
}
