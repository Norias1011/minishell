/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:51:07 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/20 15:13:07 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_export_args_null(char **key, char **value, int *i, int *count)
{
	*i = 0;
	*count = 0;
	*key = NULL;
	*value = NULL;
}

void	export_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*key;
	char	*value;
	int		i;
	int		count;

	init_export_args_null(&key, &value, &i, &count);
	if (cmd_lst->args == NULL)
		return (env_built(minishell, cmd_lst));
	check_export(cmd_lst->args, &i, &count, minishell);
	if (cmd_lst->args[i] == '=')
		key = ft_substr(cmd_lst->args, i - count, count, &(minishell->garbage));
	else
		return ;
	count = 0;
	check_export_bis(cmd_lst->args, &i, &count);
	if (cmd_lst->args[i] == '\0' && key != NULL)
		value = ft_substr(cmd_lst->args, i - count, count,
				&(minishell->garbage));
	if (env_exist(minishell, key) == 0)
		add_env(minishell, key, value);
	else
		set_env_value(minishell, key, value);
	free_key_value(key, value, minishell);
}

void	check_export(char *args, int *i, int *count, t_minishell *minishell)
{
	while (args[*i] != '\0' && args[*i] != '=' && args[*i] != '-')
	{
		while (args[*i] == ' ' && args[*i] != '\0')
			(*i)++;
		if ((args[*i] > 32 && args[*i] < 65) || (args[*i] > 90 && args[*i] < 97)
			|| (args[*i] > 122 && args[*i] < 127))
		{
			write(2, " not a valid identifier", 23);
			minishell->error = 1;
			return ;
		}
		while (args[*i] != ' ' && args[*i] != '\0' && args[*i] != '='
			&& args[*i] != '-')
		{
			(*i)++;
			(*count)++;
		}
	}
	if (args[*i] == '-')
	{
		write(2, "minishell: export: `-': not a valid identifier\n", 47);
		minishell->error = 1;
	}
	return ;
}

void	check_export_bis(char *args, int *i, int *count)
{
	(*i)++;
	while (args[*i] != '\0')
	{
		while (args[*i] == ' ' && args[*i] != '\0')
			(*i)++;
		while (args[*i] != ' ' && args[*i] != '\0')
		{
			(*i)++;
			(*count)++;
		}
	}
	return ;
}

void	free_key_value(char *key, char *value, t_minishell *minishell)
{
	g_free(&(minishell->garbage), key);
	g_free(&(minishell->garbage), value);
}
