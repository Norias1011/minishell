/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:03:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/05 16:45:01 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* function to print the prompt during the while(1) loop*/
void	print_prompt(void)
{
	printf("%s░▒▓██████████████▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓▒░░▒▓███████▓▒",
		GREEN);
	printf("░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓█▓▒░      ░▒▓█▓▒░\n");
	printf("░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█");
	printf("▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░\n");
	printf("%s░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█",
		YELLOW);
	printf("▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \n");
	printf("░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓███");
	printf("█████▓▒░▒▓██████▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░        \n");
	printf("░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓");
	printf("▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \n");
	printf("%s░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓",
		RED);
	printf("▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \n");
	printf("░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓");
	printf("▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓████████▓▒░ %s\n", DEFAULT);
	printf("\n\n");
	printf("\t\t\t\t\t\t\t%sMINISHELL BY%s\n\n", CYAN, DEFAULT);
	printf("\t\t\t\t\t\t\t%sAJEANDEL & AKINZELIN%s\n\n", MAGENTA, DEFAULT);
}

t_cmds	*get_last_cmd(t_cmds *stash)
{
	if (stash == NULL)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

int	get_arg_size(t_token **liste)
{
	int		size;
	t_token	*current;

	current = *liste;
	size = 0;
	while (current && current->token != PIPE)
	{
		size += ft_strlen(current->content);
		current = current->next;
	}
	return (size);
}

/* function that we will call when we will need to clean the exit of the program
void	clean_exit(t_minishell *minishell, int exno)
{
	if (minishell)
	{
		free_all(minishell);
	}
	exit(exno);
}
 in this function we can add all the malloc that we have to free
void	free_all(t_minishell *minishell)
{
	free(minishell->prompt);
	if (minishell->env_s)
	{
		while (minishell->env_s)
		{
			free(minishell->env_s->key);
			free(minishell->env_s->value);
			minishell->env_s = minishell->env_s->next;
		}
		free(minishell->env_s);
	}
	if (minishell->cmds)
	{
		while (minishell->cmds)
		{
			free(minishell->cmds->command);
			free(minishell->cmds->args);
			free(minishell->cmds->file);
			free(minishell->cmds->redir);
			minishell->cmds = minishell->cmds->next;
		}
		free(minishell->cmds);
	}
	if (minishell->token)
	{
		while (minishell->token)
		{
			free(minishell->token->content);
			minishell->token = minishell->token->next;
		}
		free(minishell->token);
	}
}*/
