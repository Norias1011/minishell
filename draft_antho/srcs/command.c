/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:39:44 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/31 15:40:09 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_cmd_null(t_cmds *new)
{
		new->args = NULL;
		new->next = NULL;
		new->file = NULL;
		new->command = NULL;
		new->redir = NULL;
}

void	cmd_args(t_cmds *new, t_token **tkn)
{
	char *tmp;
	
	tmp = NULL;
	while ((*tkn) && (*tkn)->token != PIPE && !is_arrow(*tkn))
	{
		tmp = ft_strdup((*tkn)->content);
		if (new->args == NULL)
			new->args = tmp;
		else
			new->args = ft_strjoin(new->args, tmp);
		(*tkn) = (*tkn)->next;
	}
}

void	cmd_redir(t_cmds *new, t_token **tkn)
{
	if ((*tkn) && is_arrow(*tkn))
	{
		new->redir = strdup((*tkn)->content);
		while ((*tkn) && (*tkn)->token != STRING && (*tkn)->token != PIPE)
			(*tkn) = (*tkn)->next;
		if ((*tkn) && (*tkn)->token == STRING)
			new->file = strdup((*tkn)->content);
		(*tkn) = (*tkn)->next;
		while ((*tkn) && (*tkn)->token == SPC)
			(*tkn) = (*tkn)->next;
		while ((*tkn) && (*tkn)->token != PIPE)
			cmd_args(new,tkn);
	}
}

t_cmds	*create_cmd(t_token **tkn)
{
	t_cmds *new = malloc(sizeof(t_cmds));
	if (new == NULL)
		return (NULL);
	set_cmd_null(new);
	while ((*tkn) && (*tkn)->token == SPC)
		(*tkn) = (*tkn)->next;
	if ((*tkn) == NULL)
	{
		free(new);
		return (NULL);
	}
	new->command = strdup((*tkn)->content);
	(*tkn) = (*tkn)->next;
	if ((*tkn))
	{
		cmd_args(new, tkn);
		cmd_redir(new, tkn);
	}
	if ((*tkn) != NULL)
		(*tkn) = (*tkn)->next;
	return (new);
}

t_cmds	*token_to_commands(t_token *tkn)
{
	t_cmds *cmd_list;
	t_cmds *new;
	
	new = NULL;
	cmd_list = NULL;
	while (tkn)
	{
		new = create_cmd(&tkn);
		if (new == NULL)
			return (NULL);
		add_command(&cmd_list, new);
	}
	return (cmd_list);
}

