/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:03:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/31 15:42:07 by akinzeli         ###   ########.fr       */
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
		RED);
	printf("▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \n");
	printf("░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓███");
	printf("█████▓▒░▒▓██████▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░        \n");
	printf("░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓");
	printf("▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \n");
	printf("%s░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓",
		YELLOW);
	printf("▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \n");
	printf("░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓");
	printf("▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓████████▓▒░ %s\n", DEFAULT);
	printf("\n\n");
	printf("\t\t\t\t\t\t\t%sMINISHELL BY%s\n\n", CYAN, DEFAULT);
	printf("\t\t\t\t\t\t\t%sAJEANDEL & AKINZELIN%s\n\n", MAGENTA, DEFAULT);
}
/* function that we will call when we will need to clean the exit of the program*/
void	clean_exit(t_minishell *minishell, int exno)
{
	if (minishell)
	{
		free_all(minishell);
	}
	exit(exno);
}
/* in this function we can add all the malloc that we have to free*/
void	free_all(t_minishell *minishell)
{
	if (minishell->env_s)
	{
		while (minishell->env_s)
		{
			free(minishell->env_s->key);
			free(minishell->env_s->value);
			free(minishell->env_s);
			minishell->env_s = minishell->env_s->next;
		}
	}
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

char	*get_token_name(t_token_lex token) // pour print les tokens
{
	if (token == STRING)
		return ("STRING");
	if (token == SYMBOL)
		return ("SYMBOL");
	if (token == SPC)
		return ("SPC");
	if (token == PIPE)
		return ("PIPE");
	if (token == DOLLAR)
		return ("DOLLAR");
	if (token == DASH)
		return ("DASH");
	if (token == QUOTE)
		return ("QUOTE");
	if (token == DOUBLEQUOTE)
		return ("DOUBLEQUOTE");
	if (token == L_ARROW)
		return ("L_ARROW");
	if (token == R_ARROW)
		return ("R_ARROW");
	if (token == QUOTE_STRING)
		return ("QUOTE_STRING");
	if (token == L_D_ARROW)
		return ("L_D_ARROW");
	if (token == R_D_ARROW)
		return ("R_D_ARROW");
	return ("UNKNOW");
}