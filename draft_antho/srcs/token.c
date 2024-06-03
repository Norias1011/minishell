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

void	add_command(t_cmds **cmd_list, char *command, char *args, char *file,
		char *redir)
{
	t_cmds	*new_cmd;
	t_cmds	*last;

	new_cmd = malloc(sizeof(t_cmds));
	if (new_cmd == NULL)
		return ;
	new_cmd->command = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	new_cmd->file = NULL;
	new_cmd->redir = NULL;
	if (args != NULL)
		new_cmd->args = strdup(args);
	if (command != NULL)
		new_cmd->command = strdup(command);
	if (file != NULL)
		new_cmd->file = strdup(file);
	if (redir != NULL)
		new_cmd->redir = strdup(redir);
	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		last = get_last_cmd(*cmd_list);
		last->next = new_cmd;
	}
}

t_cmds	*token_to_commands(t_token *token_list)
		// transforme les tokens en une liste de commande en gros
{
	t_cmds *cmd_list;
	t_token *current;
	char *cmd;
	char *args;
	char *file;
	char *redir;
	int arg_size;

	cmd_list = NULL;
	current = token_list;
	cmd = NULL;
	args = NULL;
	file = NULL;
	redir = NULL;
	arg_size = 0;
	while (current)
	{
		while (current && current->token == SPC) // recuperation de la commande
			current = current->next;
		if (current == NULL)
			break ;
		cmd = strdup(current->content);
		current = current->next;
		if (current)
		{
			arg_size = get_arg_size(&current);
			args = malloc(sizeof(char) * (arg_size + 1));
			if (args == NULL)
				return (NULL);
			args[0] = '\0';
			while (current && (current->token != PIPE
					&& current->token != L_ARROW && current->token != R_ARROW
					&& current->token != L_D_ARROW
					&& current->token != R_D_ARROW))
				// tant que y a pas de redirection et que c'est pas fin de la commande
			{
				args = ft_strjoin(args, current->content);
					// on recupere les args
				current = current->next;
			}
			if (current && (current->token == L_ARROW
					|| current->token == R_ARROW || current->token == L_D_ARROW
					|| current->token == R_D_ARROW)) // si y a les redirections
			{
				redir = strdup(current->content);
				while (current && (current->token != STRING
						&& current->token != PIPE))
					// on cherche le nom de fichier s'il y en a un
					current = current->next;
				if (current && current->token == STRING)
					// si y a un nom de fichier on le prend
					file = strdup(current->content);
				while (current && current->token != PIPE)
					// on vire le reste jusqu au pipe ou a la fin
					current = current->next;
			}
		}
		if (current) // passe la pipe si on est pas a la fin
			current = current->next;
		add_command(&cmd_list, cmd, args, file, redir);
		free(args);
		cmd = NULL;
		args = NULL;
		file = NULL;
		redir = NULL;
		arg_size = 0;
	}
	return (cmd_list);
}

int	token_string(char *rl, t_token *new, int i)
{
	int	j;

	j = 0;
	while ((rl[i + j]) && (is_metachar(rl[i + j]) == 0))
		j++;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = STRING;
	return (j);
}

int	token_space(char *rl, t_token *new, int i)
{
	int	j;

	j = 0;
	while (rl[i + j] == ' ')
		j++;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = SPC;
	return (j);
}

int	token_symbol(char *rl, t_token *new, int i)
{
	int j;

	j = 1;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = get_symbol(new->content);
	return (j);
}