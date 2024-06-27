/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:57:47 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/25 15:00:16 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_mini_shell(t_minishell *minishell, char **env)
{
	t_garbage	*garbage;

	garbage = NULL;
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->garbage = garbage;
	if (!init_env(minishell, env, 0))
	{
		printf("Error: init_env failed\n");
		return (0);
	}
	if (!init_cd(minishell))
	{
		printf("Error: init_cd failed\n");
		return (0);
	}
	minishell->prompt = NULL;
	minishell->env = env;
	minishell->error = 0;
	minishell->echo_flag = 0;
	return (1);
}

int	init_env(t_minishell *minishell, char **env, int i)
{
	t_env	*new_env;
	t_env	*tmp;

	while (env[i])
	{
		new_env = g_malloc(&(minishell->garbage), sizeof(t_env));
		if (!new_env)
			return (0);
		new_env->key = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i],
				&(minishell->garbage));
		new_env->value = ft_strdup(ft_strchr(env[i], '=') + 1,
				&(minishell->garbage));
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
		i++;
	}
	return (1);
}

char	*get_env_value(t_minishell *minishell, char *key)
{
	t_env	*tmp;

	tmp = minishell->env_s;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_pwd(t_minishell *minishell)
{
	char	*logname;
	char	*tmp;
	char	*logname_color;
	char	*pwd;
	char	*final_prompt;

	logname = get_env_value(minishell, "LOGNAME");
	if (logname == NULL)
		return ("Minishell > ");
	tmp = ft_strjoin(logname, ":", &(minishell->garbage));
	logname_color = ft_strjoin(CYAN, tmp, &(minishell->garbage));
	pwd = get_env_value(minishell, "PWD");
	if (pwd == NULL)
		return ("Minishell > ");
	pwd = ft_strjoin(MAGENTA, pwd, &(minishell->garbage));
	final_prompt = ft_strjoin(logname_color, pwd, &(minishell->garbage));
	final_prompt = ft_strjoin(final_prompt, DEFAULT, &(minishell->garbage));
	final_prompt = ft_strjoin(final_prompt, "$ ", &(minishell->garbage));
	return (final_prompt);
}

void	set_env_value(t_minishell *minishell, char *key, char *val)
{
	t_env	*tmp;

	tmp = minishell->env_s;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			g_free(&(minishell->garbage), tmp->value);
			tmp->value = ft_strdup(val, &(minishell->garbage));
			return ;
		}
		tmp = tmp->next;
	}
}
