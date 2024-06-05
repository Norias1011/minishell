/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:13 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/06 01:05:30 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* function that we will call when we will need to clean the exit of the program*/
void	clean_exit(t_minishell *minishell, int exno)
{
	free_all(minishell);
	exit(exno);
}
/* in this function we can add all the malloc that we have to free*/
void	free_all(t_minishell *minishell)
{
	if (minishell->cmds)
		free_cmds(minishell->cmds);
	if (minishell->token)
		free_token(minishell->token);
	if (minishell->env_s)
		free_env(minishell->env_s);
	free_garbage(minishell->garbage);
	if (minishell->env)
		free(minishell->env);
}

void	free_cmd(t_cmds *cmd)
{
	if (cmd->command)
		free(cmd->command);
	if (cmd->args)
		free(cmd->args);
	if (cmd->file)
		free(cmd->file);
	free(cmd);
}

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_cmd(tmp);
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_garbage(t_garbage *garbage)
{
	t_garbage	*tmp;

	while (garbage != NULL)
	{
		tmp = garbage;
		if (garbage->value)
			free(garbage->value);
		garbage = garbage->next;
		free(tmp);
	}
}

void	free_file(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file;
		file = file->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->redir)
			free(tmp->redir);
		free(tmp);
	}
}

/*int	is_char_double_pointer(void *value)
{
	char	**values;
	int		i;

	values = (char **)value;
	i = 0;
	while (values[i])
	{
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}*/

/*void	free_garbage(t_garbage *garbage)
{
	t_garbage	*tmp;
	char		**values;
	int			i;

	while (garbage)
	{
		tmp = garbage;
		garbage = garbage->next;
		if (tmp->value)
		{
			if (is_char_double_pointer(tmp->value))
			{
				values = (char **)tmp->value;
				i = 0;
				while (values[i])
				{
					free(values[i]);
					i++;
				}
			}
			free(tmp->value);
		}
		free(tmp);
	}
}*/
