/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:36:00 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/31 15:36:19 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_paths(t_cmds *cmd, t_env *env) // split les paths
{
	t_env *current;
	char **paths;
	char **result;
	int i;

	paths = NULL;
	result = NULL;
	i = 0;
	current = env;
	while (current && strncmp(current->key, "PATH", 4) != 0)
		// vas chercher la value a la key path
		current = current->next;
	if (current)
		paths = ft_split(current->value, ':');
	if (paths)
	{
		while (paths[i])
			i++;
		result = malloc((i + 1) * sizeof(char *));
		i = 0;
		while (paths[i])
		{
			result[i] = ft_strjoin(paths[i], "/");
			result[i] = ft_strjoin(result[i], cmd->command);
			free(paths[i]);
			i++;
		}
		result[i] = NULL;
		free(paths);
	}
	return (result);
}
