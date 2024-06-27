/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:03:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/10 10:24:32 by akinzeli         ###   ########.fr       */
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

void	status_child(t_minishell *mini, int status)
{
	if (WIFEXITED(status))
		mini->error = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		mini->error = WTERMSIG(status);
		if (mini->error != 131)
			mini->error += 128;
	}
}

void	pipe_redir(t_cmds **cmd_lst, t_minishell *mini)
{
	if ((*cmd_lst)->file)
		handle_redir(*cmd_lst, mini->env_s, mini->env, mini);
}
