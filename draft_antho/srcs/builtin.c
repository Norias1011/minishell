/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:53:37 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/04 17:14:42 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_cmds *cmd_lst)
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
	while (cmd_lst->args[i] != '\0' && cmd_lst->args[i] == ' ')
		i++;
	if (((cmd_lst->args[i] != '\0') && (strncmp(cmd_lst->args + i, "-n",
					3) == 0)) && ((cmd_lst->args[i + 2] == ' ')
			|| cmd_lst->args[i + 2] == '\0' || (cmd_lst->args[i + 2] == 'n')))
	{
		i += 2;
		new_line = 0;
		while (cmd_lst->args[i] != '\0' && cmd_lst->args[i] == 'n')
			i++;
	}
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
	char	*pwd;

	(void)cmd_lst;
	pwd = get_env_value(minishell, "PWD");
	if (pwd == NULL)
	{
		printf("Error: get_env_value failed\n");
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
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
	key = ft_substr(cmd_lst->args, i - count, count);
	if (env_exist(minishell, key) == 1)
	{
		remove_env(minishell, key);
		free(key);
	}
	else
	{
		free(key);
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
