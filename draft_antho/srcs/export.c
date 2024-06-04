/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:51:07 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/04 17:14:16 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*key;
	char	*value;
	int		i;
	int		count;

	i = 0;
	count = 0;
	key = NULL;
	value = NULL;
	if (cmd_lst->args == NULL)
		return (env_built(minishell, cmd_lst));
	check_export(cmd_lst->args, &i, &count);
	if (cmd_lst->args[i] == '=')
		key = ft_substr(cmd_lst->args, i - count, count);
	else
		return ;
	count = 0;
	check_export_bis(cmd_lst->args, &i, &count);
	if (cmd_lst->args[i] == '\0' && key != NULL)
		value = ft_substr(cmd_lst->args, i - count, count);
	if (env_exist(minishell, key) == 0)
		add_env(minishell, key, value);
	else
		set_env_value(minishell, key, value);
	free_key_value(key, value);
}

void	check_export(char *args, int *i, int *count)
{
	while (args[*i] != '\0' && args[*i] != '=')
	{
		while (args[*i] == ' ' && args[*i] != '\0')
			(*i)++;
		while (args[*i] != ' ' && args[*i] != '\0' && args[*i] != '=')
		{
			(*i)++;
			(*count)++;
		}
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

void	free_key_value(char *key, char *value)
{
	free(key);
	free(value);
}
