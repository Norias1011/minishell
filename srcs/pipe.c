/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:34:26 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/21 17:53:50 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_builtin(int nbr_cmd, t_cmds **cmd_lst, t_minishell *mini)
{
	if (nbr_cmd == 1 && is_builtin((*cmd_lst)->command) == 1)
	{
		if ((*cmd_lst)->file)
		{
			if ((*cmd_lst)->file->name != NULL)
				handle_redir(*cmd_lst, mini->env_s, mini->env, mini);
			else
				printf("syntax error : unexpected token\n");
		}
		else
		{
			execute_command(*cmd_lst, mini->env_s, mini->env, mini);
		}
		return (1);
	}
	return (0);
}

void	exec_pipes(int i, int nbr_cmd, int (*fd)[2])
{
	if (i == 0 && nbr_cmd > 1)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][0]);
		close(fd[i][1]);
	}
	else if (i == nbr_cmd - 1 && i > 0)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][1]);
		close(fd[i - 1][0]);
	}
	else if (nbr_cmd > 1)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i - 1][1]);
		close(fd[i][0]);
		close(fd[i - 1][0]);
		close(fd[i][1]);
	}
}

void	close_and_wait(int nbr_cmd, int (*fd)[2], t_minishell *mini, pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < nbr_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < nbr_cmd)
	{
		waitpid(pid[i], &status, 0);
		status_child(mini, status);
		i++;
	}
	g_free(&(mini->garbage), pid);
	g_free(&(mini->garbage), fd);
}

void	skip_cmd(t_cmds **cmd_lst, int i, int nbr_cmd, int (*fd)[2])
{
	while ((*cmd_lst)->next && is_builtin((*cmd_lst)->command) == 0
		&& is_builtin((*cmd_lst)->next->command) == 1)
		(*cmd_lst) = (*cmd_lst)->next;
	exec_pipes(i, nbr_cmd, fd);
}

void	pipe_pipe(t_cmds **cmd_lst, t_minishell *mini, int nbr_cmd)
{
	int		i;
	int		(*fd)[2];
	pid_t	*pid;

	if (pipe_builtin(nbr_cmd, cmd_lst, mini) == 1)
		return ;
	malloc_pipe(&fd, &pid, nbr_cmd, mini);
	init_pipes(fd, nbr_cmd);
	i = 0;
	while (i < nbr_cmd)
	{
		pid_handler(i, pid, fd, mini);
		if (pid[i] == 0)
		{
			skip_cmd(cmd_lst, i, nbr_cmd, fd);
			pipe_redir(cmd_lst, mini);
			close_unused_pipe(i, nbr_cmd, fd);
			execute_command(*cmd_lst, mini->env_s, mini->env, mini);
			exit(EXIT_SUCCESS);
		}
		i++;
		(*cmd_lst) = (*cmd_lst)->next;
	}
	close_and_wait(nbr_cmd, fd, mini, pid);
}
