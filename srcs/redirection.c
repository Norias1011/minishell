/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:42:32 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/21 17:35:01 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_redir(t_cmds *cmd, t_env *env_s, char **env, t_minishell *mini)
{
	int	check;
	int	out;
	int	in;

	out = dup(STDOUT_FILENO);
	in = dup(STDIN_FILENO);
	check = 0;
	while (cmd->file)
	{
		handle_redir_bis(cmd, &check);
	}
	if (check == -1)
		exit(EXIT_FAILURE);
	if (strncmp(cmd->command, "REDIRHANDLER", 13) == 0)
		return ;
	execute_command(cmd, env_s, env, mini);
	close(check);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(out);
	close(in);
}

void	handle_redir_bis(t_cmds *cmd, int *check)
{
	if (cmd->file->name == NULL)
	{
		printf("syntax error : unexpected token\n");
		exit(EXIT_FAILURE);
	}
	if (strncmp(cmd->file->redir, ">>", 3) == 0)
		*check = exec_arrow_r_d(cmd->file, *check);
	else if (strncmp(cmd->file->redir, ">", 2) == 0)
		*check = exec_arrow_r(cmd->file, *check);
	else if (strncmp(cmd->file->redir, "<", 2) == 0)
		*check = exec_arrow_l(cmd->file, *check);
	else if (strncmp(cmd->file->redir, "<<", 3) == 0)
		exec_heredoc(&cmd);
	if (cmd->file)
		cmd->file = cmd->file->next;
}

/* code de base dans exec_heredoc */
/*fd_file = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (strcmp(line, (*cmd)->file->name) == 0)
				break ;
			if (write(fd_file, line, strlen(line)) == -1)
			{
				perror("write");
				break ;
			}
			if (write(fd_file, "\n", 1) == -1)
			{
				perror("write");
				break ;
			}
			free(line);
		}
		close(fd_file);*/

/* code de base dans handle_redir */
/*if (cmd->file->name == NULL)
		{
			printf("syntax error : unexpected token\n");
			exit(EXIT_FAILURE);
		}
		if (strncmp(cmd->file->redir, ">>", 3) == 0)
			check = exec_arrow_r_d(cmd->file, check);
		else if (strncmp(cmd->file->redir, ">", 2) == 0)
			check = exec_arrow_r(cmd->file, check);
		else if (strncmp(cmd->file->redir, "<", 2) == 0)
			check = exec_arrow_l(cmd->file, check);
		else if (strncmp(cmd->file->redir, "<<", 3) == 0)
			exec_heredoc(&cmd);
		if (cmd->file)
			cmd->file = cmd->file->next;*/
