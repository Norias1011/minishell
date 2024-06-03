/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:42:32 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/03 16:52:49 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_commands(t_cmds **cmd_lst) // compte le nombre de cmd dans la liste
{
	int i;
	t_cmds *current;

	current = *cmd_lst;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	handle_redirection_solo(t_cmds *current_cmd, int fd)
{
	int	fd_file;

	if (strncmp(current_cmd->redir, ">>", 2) == 0)
	{
		fd_file = open(current_cmd->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd_file, fd);
		close(fd);
		close(fd_file);
	}
	else if (strncmp(current_cmd->redir, ">", 1) == 0)
	{
		fd_file = open(current_cmd->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd_file, fd);
		close(fd);
		close(fd_file);
	}
	else if (strncmp(current_cmd->redir, "<", 1) == 0)
	{
		fd_file = open(current_cmd->file, O_RDONLY);
		dup2(fd_file, fd);
		close(fd);
		close(fd_file);
	}
}

void	handle_redirection(t_cmds *current_cmd)
{
	int	fd_file;

	if (strncmp(current_cmd->redir, ">>", 2) == 0)
	{
		fd_file = open(current_cmd->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
	}
	else if (strncmp(current_cmd->redir, ">", 1) == 0)
	{
		fd_file = open(current_cmd->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
	}
	else if (strncmp(current_cmd->redir, "<", 1) == 0)
	{
		fd_file = open(current_cmd->file, O_RDONLY);
		dup2(fd_file, STDIN_FILENO);
		close(fd_file);
	}
}

int	is_builtin(char *cmd)
{
	if (strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (strncmp(cmd, "env", 4) == 0)
		return (1);
	if (strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (strncmp(cmd, "export", 7) == 0)
		return (1);
	if (strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

void	pipe_pipe(t_cmds **cmd_lst, t_env *env_s, char **env,
		t_minishell *minishell)
// programme de pipe
{
	int nbr_cmd;
	int i;
	int(*fd)[2] = NULL;

	pid_t *pid;

	nbr_cmd = count_commands(cmd_lst);
	pid = malloc(nbr_cmd * sizeof(pid_t));
	if (!pid)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	fd = malloc((nbr_cmd) * sizeof(*fd));
	i = 0;
	while (i < nbr_cmd - 1) // init des pipes
	{
		if (pipe(fd[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	if (nbr_cmd == 1 && is_builtin((*cmd_lst)->command) == 1)
	{
		execute_command(*cmd_lst, env_s, env, minishell);
		int save_out = dup(STDOUT_FILENO);
		if ((*cmd_lst)->file)
			handle_redirection_solo(*cmd_lst, save_out);
		return ;
	}
	i = 0;
	while (i < nbr_cmd)
	// tant qu'il y a des cmd on les lance dans les pipes avec parents enfant
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit(EXIT_FAILURE);
		else if (pid[i] == 0)
		{
			if ((*cmd_lst)->file)
				// check de >> si y a on ecris dans le fichier le resultat
				handle_redirection(*cmd_lst);
			if (i == 0 && nbr_cmd > 1) // premier process
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][0]);
				close(fd[i][1]);
			}
			else if (i == nbr_cmd - 1 && i > 0)
			// dernier process ecris ce qu'il a recu du process d'avant donc le resultat
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				close(fd[i - 1][1]);
				close(fd[i - 1][0]);
			}
			else if (nbr_cmd > 1)
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				// process precent lie au process suivant v
				dup2(fd[i][1], STDOUT_FILENO); // process suivant
				close(fd[i - 1][1]);
				close(fd[i][0]);
				close(fd[i - 1][0]);
				close(fd[i][1]);
			}
			execute_command(*cmd_lst, env_s, env, minishell);
			exit(EXIT_SUCCESS);
		}
		i++;
		(*cmd_lst) = (*cmd_lst)->next;
	}
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
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(fd);
}

void	execute_command(t_cmds *cmd_lst, t_env *env_s, char **env,
		t_minishell *minishell)
// execute les commandes en checkant si elle est dans les builtins avant
{
	char **args;
	char **paths;
	int i;

	paths = split_paths(cmd_lst, env_s);
	// split tous les path possibles en tableau avec le nom de la commande a la fin
	args = ft_split(ft_strjoin(cmd_lst->command, cmd_lst->args), ' ');
	// split tous les arguments dans un tableau d'arguments
	i = 0;
	if (strncmp(cmd_lst->command, "exit", 4) == 0)
		perror("exit");
	else if (strncmp(cmd_lst->command, "echo", 5) == 0)
		echo(cmd_lst);
	else if (strncmp(cmd_lst->command, "pwd", 4) == 0)
		pwd(minishell, cmd_lst);
	else if (strncmp(cmd_lst->command, "env", 4) == 0)
		env_built(minishell, cmd_lst);
	else if (strncmp(cmd_lst->command, "cd", 3) == 0)
		cd_built(minishell, cmd_lst);
	else if (strncmp(cmd_lst->command, "export", 7) == 0)
		export_built(minishell, cmd_lst);
	else if (strncmp(cmd_lst->command, "unset", 6) == 0)
		unset_built(minishell, cmd_lst);
	else
	{
		while (paths[i])
		{
			if (execve(paths[i], args, env) != -1) // execute
				return ;
			i++;
		}
		free(paths);
		free(args);
		perror(cmd_lst->command);
		exit(-1);
	}
	i = 0;
	while (paths && paths[i]) // free tout
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	free(args);
}
