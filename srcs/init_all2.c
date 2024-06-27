/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:57:47 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/20 16:47:25 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_exist(t_minishell *minishell, char *key)
{
	t_env	*tmp;

	tmp = minishell->env_s;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	add_env(t_minishell *minishell, char *key, char *value)
{
	t_env	*new_env;
	t_env	*tmp;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (0);
	new_env->key = ft_strdup(key, &(minishell->garbage));
	new_env->value = ft_strdup(value, &(minishell->garbage));
	new_env->next = NULL;
	if (!minishell->env_s)
		minishell->env_s = new_env;
	else
	{
		tmp = minishell->env_s;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_env;
	}
	return (1);
}

void	remove_env(t_minishell *minishell, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = minishell->env_s;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				minishell->env_s = tmp->next;
			g_free(&(minishell->garbage), tmp->key);
			g_free(&(minishell->garbage), tmp->value);
			g_free(&(minishell->garbage), tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	init_cd(t_minishell *minishell)
{
	char	*pwd;
	char	*oldpwd;

	pwd = get_env_value(minishell, "PWD");
	if (pwd == NULL)
	{
		printf("Error: get_env_value failed\n");
		return (0);
	}
	set_env_value(minishell, "OLDPWD", pwd);
	oldpwd = getcwd(NULL, 0);
	g_add(&(minishell->garbage), oldpwd);
	if (oldpwd == NULL)
	{
		printf("Error: getcwd failed\n");
		return (0);
	}
	set_env_value(minishell, "PWD", oldpwd);
	return (1);
}
