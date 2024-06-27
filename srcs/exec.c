/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:42:32 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/24 18:37:02 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_builtin(t_minishell *minishell, t_cmds *cmd_lst)
{
	if (strncmp(cmd_lst->command, "exit", 4) == 0)
		exit_built(minishell, cmd_lst);
	else if (strncmp(cmd_lst->command, "echo", 5) == 0)
		echo(cmd_lst, minishell);
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
}

void	free_args_and_path(char **args, char **paths, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		g_free(&(minishell->garbage), paths[i]);
		i++;
	}
	i = 0;
	while (args && args[i])
	{
		g_free(&(minishell->garbage), args[i]);
		i++;
	}
	g_free(&(minishell->garbage), paths);
	g_free(&(minishell->garbage), args);
}

void	free_execve(t_cmds *cmd, char **args, char **paths, t_minishell *mini)
{
	(void)cmd;
	g_free(&(mini->garbage), paths);
	g_free(&(mini->garbage), args);
	mini->error = 127;
	strerror(mini->error);
	write(2, " command not found\n", 19);
	exit(mini->error);
}

void	execute_command(t_cmds *cmd_lst, t_env *env_s, char **env,
		t_minishell *minishell)
{
	char	**args;
	char	**paths;
	char	*tmp;
	int		i;

	paths = split_paths(&cmd_lst, env_s, minishell);
	tmp = ft_strjoin(cmd_lst->command, cmd_lst->args, &(minishell->garbage));
	args = ft_split_modified(tmp, ' ', &(minishell->garbage));
	g_free(&(minishell->garbage), tmp);
	i = 0;
	if (is_builtin(cmd_lst->command))
		exec_builtin(minishell, cmd_lst);
	else
	{
		while (paths != NULL && paths[i])
		{
			if (execve(paths[i], args, env) != -1)
				return ;
			i++;
		}
		free_execve(cmd_lst, args, paths, minishell);
	}
	free_args_and_path(args, paths, minishell);
}
