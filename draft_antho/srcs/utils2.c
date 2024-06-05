/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:03:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/04 11:50:43 by akinzeli         ###   ########.fr       */
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
