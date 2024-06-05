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
