/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:35:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/11 16:57:46 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//SORT_BUILTINGS- export - unset - cd - pwd - echo
//REALLOC_ENV
//ALLOC_NEW_VARS

#include "../include/minishell.h"

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
        ft_lstadd_back(&shell->my_env->list_var_real, ft_lstnew(shell->my_env->var_real[i]));
}

int replace_repeated(t_list *temp_env, t_list *temp_var)
{
	int len;

	while (temp_env)
	{
		len = ft_strlen((char *)temp_var->content)
		   	- ft_strlen(ft_strchr((char *)temp_var->content, '='));
		if (!ft_strncmp((char *)temp_var->content, (char *)temp_env->content, len))
		{
			free(temp_env->content);
			temp_env->content = ft_strdup(temp_var->content);
			return (0);
		}
		temp_env = temp_env->next;
	}
	return (1);
}	

void replace_env(t_shell *shell) 
{
	t_list *temp_var;
	
	temp_var = shell->my_env->list_var_real;
	while (temp_var)
	{
			if (!replace_repeated(shell->my_env->list_env, temp_var))
				break;
			else
				ft_lstadd_back(&shell->my_env->list_env, ft_lstnew((char *)temp_var->content));
			temp_var = temp_var->next;
	}
	ft_freelist(&shell->my_env->list_var_real);
}


char **convert_list_array(t_shell *shell)
{
	char **new_env;
	int i;

	i = -1;
	
	shell->my_env->nbr_env = ft_lstsize(shell->my_env->list_env);
	new_env= (char **)malloc(sizeof(char *) * shell->my_env->nbr_env + 1);
	if (!new_env)
		exit(1);
	while (shell->my_env->list_env)
	{
		new_env[++i] = ft_strdup((char *)shell->my_env->list_env->content);
		shell->my_env->list_env = shell->my_env->list_env->next;
	}
	new_env[shell->my_env->nbr_env] = NULL;
	free_double(shell->my_env->env);
	shell->my_env->env = NULL;
	return (new_env);
}
   
void    ft_sort_builtins(t_shell **shell)
{
    if (ft_strcmp((*shell)->my_pro->child->command_real[0], "export"))
	{
		ft_export(*shell);
		create_lists(*shell);
		replace_env((*shell));
		(*shell)->my_env->env = convert_list_array(*shell);
		int i =-1;
		while ((*shell)->my_env->env[++i])
			printf("env= %s\n", (*shell)->my_env->env[i]);
	}
	exit(0);
}
