/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:36:00 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/06 01:05:38 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_paths(t_cmds *cmd, t_env *env, t_minishell *minishell)
{
	t_env	*current;
	char	**paths;
	char	**result;
	int		i;

	paths = NULL;
	result = NULL;
	i = 0;
	current = env;
	while (current && strncmp(current->key, "PATH", 4) != 0)
		current = current->next;
	if (current)
		paths = ft_split(current->value, ':');
	if (paths)
	{
		while (paths[i])
			i++;
		result = malloc((i + 1) * sizeof(char *));
		if (!result)
			return (NULL);
		add_garbage(&(minishell->garbage), result);
		i = 0;
		while (paths[i])
		{
			result[i] = ft_strjoin(paths[i], "/");
			add_garbage(&(minishell->garbage), result[i]);
			result[i] = ft_strjoin(result[i], cmd->command);
			add_garbage(&(minishell->garbage), result[i]);
			free(paths[i]);
			i++;
		}
		result[i] = NULL;
		free(paths);
	}
	return (result);
}
