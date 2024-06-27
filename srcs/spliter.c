/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:36:00 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/21 17:44:27 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	**create_paths(char **paths, t_cmds *cmd, t_minishell *mini)
{
	int		i;
	char	**result;

	i = 0;
	result = NULL;
	if (paths)
	{
		while (paths[i])
			i++;
		result = g_malloc(&(mini->garbage), (i + 1) * sizeof(char *));
		if (!result)
			return (NULL);
		i = 0;
		while (paths[i])
		{
			result[i] = ft_strjoin(paths[i], "/", &(mini->garbage));
			result[i] = ft_strjoin(result[i], cmd->command, &(mini->garbage));
			g_free(&(mini->garbage), paths[i]);
			i++;
		}
		result[i] = NULL;
		g_free(&(mini->garbage), paths);
	}
	return (result);
}

char	**split_paths(t_cmds **cmd, t_env *env, t_minishell *minishell)
{
	t_env	*current;
	char	**paths;
	int		i;

	current = env;
	paths = NULL;
	i = ft_strlen((*cmd)->command);
	while (i >= 0)
	{
		if ((*cmd)->command[0] == '/' && (*cmd)->command[i] == '/')
		{
			if (i == 0)
				return (paths);
			split_path_bis1(&i, &paths, cmd, minishell);
			return (paths);
		}
		i--;
	}
	while (current && strncmp(current->key, "PATH", 5) != 0)
		current = current->next;
	if (current)
		paths = ft_split(current->value, ':', &(minishell->garbage));
	else
		return (paths);
	return (create_paths(paths, *cmd, minishell));
}

void	split_path_bis1(int *i, char ***paths, t_cmds **cmd, t_minishell *mini)
{
	*paths = ft_split((*cmd)->command, '/', &(mini->garbage));
	*i = 0;
	while ((*paths)[*i])
		*i += 1;
	(*cmd)->command = ft_strdup((*paths)[*i - 1], &(mini->garbage));
	*i = 0;
	while ((*paths)[*i])
	{
		(*paths)[*i] = ft_strjoin("/", (*paths)[*i], &(mini->garbage));
		*i += 1;
	}
	*i = 1;
	while ((*paths)[*i])
	{
		(*paths)[0] = ft_strjoin((*paths)[0], (*paths)[*i], &(mini->garbage));
		*i += 1;
	}
}

/*code de base dans split paths*/
/*paths = ft_split((*cmd)->command, '/', &(minishell->garbage));
			i = 0;
			while (paths[i])
				i++;
			(*cmd)->command = ft_strdup(paths[i - 1], &(minishell->garbage));
			i = 0;
			while (paths[i])
			{
				paths[i] = ft_strjoin("/", paths[i], &(minishell->garbage));
				i++;
			}
			i = 1;
			while (paths[i])
			{
				paths[0] = ft_strjoin(paths[0], paths[i],
						&(minishell->garbage));
				i++;
			}*/
