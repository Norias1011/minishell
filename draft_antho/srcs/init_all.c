/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:57:47 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/03 16:52:21 by akinzeli         ###   ########.fr       */
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
	if (!init_cd(minishell))
	{
		printf("Error: init_cd failed\n");
		return (0);
	}
	minishell->prompt = NULL;
	minishell->env = env;
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
	tmp = ft_strjoin(logname, ":");
	logname_color = ft_strjoin(CYAN, tmp);
	pwd = get_env_value(minishell, "PWD");
	pwd = ft_strjoin(MAGENTA, pwd);
	final_prompt = ft_strjoin(logname_color, pwd);
	final_prompt = ft_strjoin(final_prompt, DEFAULT);
	final_prompt = ft_strjoin(final_prompt, "$ ");
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
			free(tmp->value);
			tmp->value = ft_strdup(val);
			return ;
		}
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
	if (oldpwd == NULL)
	{
		printf("Error: getcwd failed\n");
		return (0);
	}
	set_env_value(minishell, "PWD", oldpwd);
	return (1);
}

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
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
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
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
