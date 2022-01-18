/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:59:12 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/18 18:49:42 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_lists(t_shell *shell)
{
	int i;

	i = -1;
	while (shell->my_env->env[++i])
	{
		ft_lstadd_back(&shell->my_env->list_env, ft_lstnew(shell->my_env->env[i]));
	}
	i = -1;
   	while (shell->my_env->var_real[++i])
	{
		if (shell->my_env->var_real[i][0] != '=' && (ft_isalpha(shell->my_env->var_real[i][0]) || shell->my_env->var_real[i][0] == '_'))
        	ft_lstadd_back(&shell->my_env->list_var_real, ft_lstnew(shell->my_env->var_real[i]));
	}
}

int replace_first(t_list **head_env, t_list *temp_var, int replace)
{
	int len_1;
	int len_2;
	t_list *temp;
	t_list *to_free;

	temp = *head_env;
	to_free = *head_env;
	len_1 = ft_strlen((char *)temp->content)
	   	- ft_strlen(ft_strchr((char *)temp->content, '='));
	len_2 = ft_strlen((char *)temp_var->content)
	   	- ft_strlen(ft_strchr((char *)temp_var->content, '='));
	if (len_1 == len_2 && !ft_strncmp((char *)temp_var->content, (char *)(*head_env)->content, len_1))
	{
		if (replace == 1)
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

int replace_repeated(t_list **head_env, t_list *temp_var, int replace)
{
	int len_1;
	int len_2;
	t_list	*temp_back;
	t_list	*temp_env;

	if (replace_first(head_env, temp_var, replace))
		return (0);
	temp_back = *head_env;
	temp_env= temp_back->next;
	while (temp_env)
	{
		//funcion que calcula el len de 2 strings a la vez , usar tambien en replace_first())
		len_1 = ft_strlen((char *)temp_env->content)
		   	- ft_strlen(ft_strchr((char *)temp_env->content, '='));
		len_2 = ft_strlen((char *)temp_var->content)
		   	- ft_strlen(ft_strchr((char *)temp_var->content, '='));
		if (len_1 == len_2 && !ft_strncmp((char *)temp_var->content, (char *)temp_env->content, len_1))
		{
		//	free(temp_env->content); //dato curioso que no funcione S(
		//	temp_env->content = ft_strdup(temp_var->content);
			if (replace == 1)
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

void replace_env(t_shell *shell, int replace) 
{
	//REPLACE: 1=poner 0=quitar
	t_list *temp_var;

	temp_var = shell->my_env->list_var_real;
	while (temp_var)
	{
			if (replace_repeated(&shell->my_env->list_env, temp_var, replace) && replace == 1)
				ft_lstadd_back(&shell->my_env->list_env, ft_lstnew((char *)temp_var->content));
			temp_var = temp_var->next;
	}
	ft_freelist(&shell->my_env->list_var_real);
}


char **convert_list_array(t_shell *shell)
{
	char **temp_env;
	int i;

	i = -1;
	
	shell->my_env->nbr_env = ft_lstsize(shell->my_env->list_env);
	temp_env= (char **)malloc(sizeof(char *) * (shell->my_env->nbr_env + 1));
	if (!temp_env)
		status_error(strerror(errno), errno);
	while (shell->my_env->list_env)
	{
		temp_env[++i] = ft_strdup((char *)shell->my_env->list_env->content);
		shell->my_env->list_env = shell->my_env->list_env->next;
	}
	temp_env[shell->my_env->nbr_env] = NULL;
	free_double(shell->my_env->env, 2);
	shell->my_env->env = NULL;
	return (temp_env);
}
