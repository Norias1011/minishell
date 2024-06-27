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

int	exec_arrow_r_d(t_file *file, int fd_file)
{
	fd_file = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_file == -1)
		return (fd_file);
	dup2(fd_file, STDOUT_FILENO);
	return (fd_file);
}

int	exec_arrow_r(t_file *file, int fd_file)
{
	fd_file = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_file == -1)
		return (-1);
	dup2(fd_file, STDOUT_FILENO);
	return (fd_file);
}

int	exec_arrow_l(t_file *file, int fd_file)
{
	fd_file = open(file->name, O_RDONLY);
	if (fd_file == -1)
		return (-1);
	dup2(fd_file, STDIN_FILENO);
	return (fd_file);
}

void	exec_heredoc(t_cmds **cmd)
{
	int		fd_file;
	char	*line;

	line = NULL;
	while ((*cmd)->file && strncmp((*cmd)->file->redir, "<<", 3) == 0
		&& (*cmd)->file->name != NULL)
	{
		exec_heredoc_bis(&fd_file, line, cmd);
		if ((*cmd)->file->next && strncmp((*cmd)->file->next->redir, "<<",
				3) == 0 && (*cmd)->file->next->name != NULL)
			(*cmd)->file = (*cmd)->file->next;
		else
			break ;
	}
	fd_file = open("temp.txt", O_RDONLY);
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	unlink("temp.txt");
	free(line);
}

void	exec_heredoc_bis(int *fd_file, char *line, t_cmds **cmd)
{
	*fd_file = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, (*cmd)->file->name) == 0)
			break ;
		if (write(*fd_file, line, strlen(line)) == -1)
		{
			perror("write");
			break ;
		}
		if (write(*fd_file, "\n", 1) == -1)
		{
			perror("write");
			break ;
		}
		free(line);
	}
	close(*fd_file);
}
