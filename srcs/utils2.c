/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:03:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/17 11:43:38 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_command(t_cmds **cmd_list, t_cmds *new_cmd)
{
	t_cmds	*last;

	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		last = get_last_cmd(*cmd_list);
		last->next = new_cmd;
	}
}

t_file	*get_last_file(t_file *stash)
{
	if (stash == NULL)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

void	add_file(t_file **file_list, t_file *new_file)
{
	t_file	*last;

	if (*file_list == NULL)
		*file_list = new_file;
	else
	{
		last = get_last_file(*file_list);
		last->next = new_file;
	}
}

int	is_builtin(char *cmd)
{
	if (strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (strncmp(cmd, "export", 7) == 0)
		return (1);
	if (strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (strncmp(cmd, "env", 4) == 0)
		return (1);
	if (strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (strncmp(cmd, "pwd", 5) == 0)
		return (1);
	return (0);
}

int	count_commands(t_cmds **cmd_lst)
{
	int		i;
	t_cmds	*current;

	current = *cmd_lst;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
