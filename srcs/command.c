/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:39:44 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/25 13:39:39 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_args(t_cmds *new, t_token **tkn, t_minishell *minishell)
{
	char	*tmp;
	char	*arg;

	tmp = NULL;
	while (*tkn && (*tkn)->token != PIPE)
	{
		while ((*tkn) && (*tkn)->token != PIPE && !is_arrow(*tkn))
		{
			tmp = ft_strdup((*tkn)->content, &(minishell->garbage));
			if (new->args == NULL)
				new->args = tmp;
			else
			{
				arg = new->args;
				new->args = ft_strjoin(arg, tmp, &(minishell->garbage));
				g_free(&(minishell->garbage), arg);
				g_free(&(minishell->garbage), tmp);
			}
			(*tkn) = (*tkn)->next;
		}
		if ((*tkn) && is_arrow(*tkn))
			cmd_redir(new, tkn, minishell);
	}
}

void	cmd_redir(t_cmds *new, t_token **tkn, t_minishell *minishell)
{
	t_file	*file;

	file = g_malloc(&(minishell->garbage), sizeof(t_file));
	file->next = NULL;
	file->name = NULL;
	file->redir = NULL;
	file->redir = ft_strdup((*tkn)->content, &(minishell->garbage));
	while ((*tkn) && (*tkn)->token != STRING && (*tkn)->token != PIPE
		&& (*tkn)->token != DOUBLEQUOTE)
		(*tkn) = (*tkn)->next;
	if ((*tkn) && ((*tkn)->token == STRING || (*tkn)->token == DOUBLEQUOTE))
		file->name = ft_strdup((*tkn)->content, &(minishell->garbage));
	if (*tkn)
		(*tkn) = (*tkn)->next;
	while ((*tkn) && (*tkn)->token == SPC)
		(*tkn) = (*tkn)->next;
	add_file(&new->file, file);
}

t_cmds	*create_cmd(t_token **tkn, t_minishell *minishell)
{
	t_cmds	*new;

	minishell->echo_flag = 0;
	new = g_malloc(&(minishell->garbage), sizeof(t_cmds));
	if (new == NULL)
		return (NULL);
	set_cmd_null(new);
	while ((*tkn) && ((*tkn)->token == SPC || (*tkn)->content[0] == '\0'))
		(*tkn) = (*tkn)->next;
	if ((*tkn) == NULL)
		return (NULL);
	if ((*tkn)->token == L_D_ARROW)
		new->command = ft_strdup("REDIRHANDLER", &(minishell->garbage));
	else
	{
		new->command = ft_strdup((*tkn)->content, &(minishell->garbage));
		(*tkn) = (*tkn)->next;
	}
	create_cmd_bis(tkn, minishell, new);
	if ((*tkn))
		cmd_args(new, tkn, minishell);
	if ((*tkn) != NULL)
		(*tkn) = (*tkn)->next;
	return (new);
}

void	create_cmd_bis(t_token **tkn, t_minishell *minishell, t_cmds *new)
{
	if ((*tkn) && (*tkn)->token == SPC && (strncmp(new->command, "echo",
				5) == 0))
		(*tkn) = (*tkn)->next;
	if ((*tkn) && (strncmp(new->command, "echo", 5) == 0)
		&& ((*tkn)->token == DOUBLEQUOTE))
		minishell->echo_flag = 1;
}

t_cmds	*token_to_commands(t_token *tkn, t_minishell *minishell)
{
	t_cmds	*cmd_list;
	t_cmds	*new;

	new = NULL;
	cmd_list = NULL;
	while (tkn)
	{
		new = create_cmd(&tkn, minishell);
		if (new == NULL)
			return (NULL);
		add_command(&cmd_list, new);
	}
	return (cmd_list);
}

/*if ((*tkn) && (*tkn)->token == SPC && (strncmp(new->command, "echo", 5) == 0))
		(*tkn) = (*tkn)->next;
	if ((*tkn) && (strncmp(new->command, "echo", 5) == 0)
		&& ((*tkn)->token == DOUBLEQUOTE))
		minishell->echo_flag = 1;*/
