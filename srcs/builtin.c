/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:53:37 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/25 13:15:23 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo_n(t_cmds *cmd_lst, int i, int *new_line)
{
	int	j;

	if (cmd_lst->args[i] != '\0' && cmd_lst->args[i] == ' '
		&& (strncmp(cmd_lst->args + (i + 1), "-n", 2) == 0))
		i++;
	if (((cmd_lst->args[i] != '\0') && (strncmp(cmd_lst->args + i, "-n",
					2) == 0)) && ((cmd_lst->args[i + 2] == ' ')
			|| cmd_lst->args[i + 2] == '\0' || (cmd_lst->args[i + 2] == 'n')))
	{
		*new_line = 0;
		j = 2;
		while (cmd_lst->args[i + j] != '\0' && cmd_lst->args[i + j] == 'n')
			j++;
		if (cmd_lst->args[i + j] != '\0' && cmd_lst->args[i + j] != ' ')
		{
			*new_line = 1;
			return (i);
		}
		else
			i = i + j + 1;
	}
	return (i);
}

void	echo(t_cmds *cmd_lst, t_minishell *minishell)
{
	int	new_line;
	int	i;

	i = 0;
	new_line = 1;
	if (cmd_lst->args == NULL)
	{
		printf("\n");
		return ;
	}
	if (minishell->echo_flag == 0)
		i = echo_n(cmd_lst, i, &new_line);
	if (new_line == 0)
		i = echo_n_loop(cmd_lst, i);
	while (cmd_lst->args[i] != '\0')
	{
		if (cmd_lst->args[i] != '\0')
			printf("%c", cmd_lst->args[i]);
		i++;
	}
	if (new_line == 1)
		printf("\n");
}

void	pwd(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*pwd2;

	(void)cmd_lst;
	pwd2 = get_env_value(minishell, "PWD");
	if (pwd2 == NULL)
	{
		printf("Error: get_env_value failed\n");
		return ;
	}
	printf("%s\n", pwd2);
}

void	unset_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*key;
	int		i;
	int		count;

	key = NULL;
	i = 0;
	count = 0;
	if (cmd_lst->args == NULL)
		return ;
	check_unset(cmd_lst->args, &i, &count);
	key = ft_substr(cmd_lst->args, i - count, count, &(minishell->garbage));
	if (env_exist(minishell, key) == 1)
	{
		remove_env(minishell, key);
		g_free(&(minishell->garbage), key);
	}
	else
	{
		g_free(&(minishell->garbage), key);
		return ;
	}
}

void	check_unset(char *args, int *i, int *count)
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
