/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:11:46 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/29 14:08:44 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_commands(t_cmds **cmd_lst) // compte le nombre de cmd dans la liste
{
	int		i;
	t_cmds	*current;

	current = *cmd_lst;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	pipe_pipe(t_cmds **cmd_lst, t_env *env_s, char **env) // programme de pipe
{
	int		nbr_cmd;
	int		i;
	pid_t	*pid;
	t_cmds	*current_cmd;

	nbr_cmd = count_commands(cmd_lst);
	pid = malloc(nbr_cmd * sizeof(pid_t));
	int(*fd)[2] = malloc((nbr_cmd) * sizeof(*fd));
	current_cmd = *cmd_lst;
	i = 0;
	while (i < nbr_cmd - 1) // init des pipes
	{
		if (pipe(fd[i]) == -1)
			exit(-1);
		i++;
	}
	i = 0;
	while (current_cmd) //tant qu'il y a des cmd on les lance dans les pipes avec parents / enfant -parent / enfant -parent etc
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit(-1);
		else if (pid[i] == 0)
		{
			if (i > 0)
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				close(fd[i - 1][0]);
			}
			if (i < nbr_cmd - 1)
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			execute_command(current_cmd, env_s, env);
			exit(0);
		}
		i++;
		current_cmd = current_cmd->next;
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
}

void	echo(t_cmds *cmd_lst) // cmd echo
{
	int	new_line;
	int	i;

	i = 0;
	new_line = 0;
	while (cmd_lst->args[i] && cmd_lst->args[i] == ' ')
		i++;
	if (strncmp(cmd_lst->args + i, "-n", 2) == 0)
	{
		new_line = 1;
		i += 2;
	}
	while (cmd_lst->args[i] && cmd_lst->args[i] == ' ')
		i++;
	printf("%s", cmd_lst->args + i);
	if (new_line == 0) // newline en fonction du booleen
		printf("\n");
}

void	execute_command(t_cmds *cmd_lst, t_env *env_s, char **env) // execute les commandes en checkant si elle est dans les builtins avant
{
	char **args;
	char **paths;
	int	i;
	
	paths = split_paths(cmd_lst, env_s); //split tous les path possibles en tableau avec le nom de la commande a la fin
	args = ft_split(cmd_lst->args, ' '); // split tous les arguments dans un tableau d'arguments
	i = 0;
	if (!cmd_lst->command)
	{
		free(paths);
		free(args);
		return ;
	}
	if (strncmp(cmd_lst->command, "exit", 4) == 0)
	{
		exit(1);
	}
	else if (strncmp(cmd_lst->command, "echo", 5) == 0)
		echo(cmd_lst);
	else
	{
		while (paths[i])
		{
			if (execve(paths[i], args, env) != -1) // execute 
				break;
			i++;
		}
		exit (-1);
	}
	i = 0;
	while (paths && paths[i]) //free tout
	{
        	free(paths[i]);
        	i++;
    	}
    	free(paths);
    	free(args);
}

void	minishell_loop(t_minishell *minishell)
{
	//char	**cmd;

	print_prompt();
	while (1)
	{
		signal_handler();
		minishell->prompt = NULL;
		minishell->prompt = readline("minishell$ > ");
		if (!minishell->prompt)
			clean_exit(minishell, EXIT_SUCCESS);
		/*cmd = ft_split(minishell->prompt, ' ');
		if (!cmd)
		{
			free(minishell->prompt);
			clean_exit(minishell, EXIT_FAILURE);
		}*/
		token(minishell->prompt, &minishell->token);
		minishell->cmds = token_to_commands(minishell->token);
		free(minishell->prompt);
		minishell->token = NULL;
		pipe_pipe(&minishell->cmds, minishell->env_s, minishell->env);
		/*parse_cmd(cmd);
		free(line);
		free(cmd);*/
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	minishell;

	(void)argc, (void)argv;
	minishell.env = env;
	if (init_mini_shell(&minishell, env) == -1)
		clean_exit(&minishell, EXIT_FAILURE);
	minishell_loop(&minishell);
	return (0);
}
