/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:13 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/05 17:00:40 by akinzeli         ###   ########.fr       */
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
	if (minishell->garbage)
		free_garbage(minishell->garbage);
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
	t_garbage *tmp;

	while (garbage)
	{
		tmp = garbage;
		garbage = garbage->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}