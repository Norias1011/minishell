/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:57:47 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/29 16:39:51 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_mini_shell(t_minishell *minishell, char **env)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	if (!init_env(minishell, env))
	{
		printf("Error: init_env failed\n");
		return (0);
	}
	// init working directory
	// init le reste
	return (1);
}

int	init_env(t_minishell *minishell, char **env)
{
	int		i;
	t_env	*new_env;
	t_env	*tmp;

	i = 0;
	while (env[i])
	{
		new_env = (t_env *)malloc(sizeof(t_env));
		printf("Je malloc dans init_env\n");
		if (!new_env)
			return (0);
		new_env->key = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		new_env->value = ft_strdup(ft_strchr(env[i], '=') + 1);
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
		printf("key: %s\n", new_env->key);
		printf("value: %s\n", new_env->value);
		i++;
	}
	return (1);
}
