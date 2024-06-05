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
	new->command = NULL;
	new->file = NULL;
}

void	cmd_args(t_cmds *new, t_token **tkn)
{
	char	*tmp;
	char	*arg;

	tmp = NULL;
	while (*tkn && (*tkn)->token != PIPE)
	{
		while ((*tkn) && (*tkn)->token != PIPE && !is_arrow(*tkn))
		{
			tmp = ft_strdup((*tkn)->content);
			if (new->args == NULL)
				new->args = tmp;
			else
			{
				arg = new->args;
				new->args = ft_strjoin(arg, tmp);
				free(arg);
				free(tmp);
			}
			(*tkn) = (*tkn)->next;
		}
		if ((*tkn) && is_arrow(*tkn))
			cmd_redir(new, tkn);
	}
}

void	cmd_redir(t_cmds *new, t_token **tkn)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->next = NULL;
	file->name = NULL;
	file->redir = NULL;
	file->redir = strdup((*tkn)->content);
	while ((*tkn) && (*tkn)->token != STRING && (*tkn)->token != PIPE)
		(*tkn) = (*tkn)->next;
	if ((*tkn) && (*tkn)->token == STRING)
		file->name = strdup((*tkn)->content);
	if (*tkn)
		(*tkn) = (*tkn)->next;
	while ((*tkn) && (*tkn)->token == SPC)
		(*tkn) = (*tkn)->next;
	add_file(&new->file, file);
}

t_cmds	*create_cmd(t_token **tkn)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (new == NULL)
		return (NULL);
	set_cmd_null(new);
	while ((*tkn) && (*tkn)->token == SPC)
		(*tkn) = (*tkn)->next;
	if ((*tkn) == NULL)
		return (NULL);
	new->command = strdup((*tkn)->content);
	(*tkn) = (*tkn)->next;
	if ((*tkn))
		cmd_args(new, tkn);
	if ((*tkn) != NULL)
		(*tkn) = (*tkn)->next;
	return (new);
}
/*void	free_new(t_cmds *new)
{
	if (new->command)
		free(new->command);
	if (new->args)
		free(new->args);
}*/

t_cmds	*token_to_commands(t_token *tkn)
{
	t_cmds	*cmd_list;
	t_cmds	*new;

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
