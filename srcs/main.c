/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:08:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/25 16:03:50 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_minishell	minishell;

	(void)argc, (void)argv;
	if (init_mini_shell(&minishell, env) == -1)
		clean_exit(&minishell, EXIT_FAILURE);
	minishell_loop(&minishell);
	return (0);
}

void	minishell_loop(t_minishell *minishell)
{
	int	nbr_cmd;

	print_prompt();
	while (1)
	{
		signal_handler();
		minishell->prompt = NULL;
		minishell->echo_flag = 0;
		minishell->prompt = readline(get_pwd(minishell));
		signal_handler_bis();
		if (!minishell->prompt)
			clean_exit(minishell, EXIT_SUCCESS);
		else if (input_user_parser(minishell) == false)
			clean_exit(minishell, EXIT_FAILURE);
		else
		{
			token(minishell, minishell->prompt, &minishell->token);
			minishell->cmds = token_to_commands(minishell->token, minishell);
			free(minishell->prompt);
			minishell->token = NULL;
			nbr_cmd = count_commands(&minishell->cmds);
			pipe_pipe(&minishell->cmds, minishell, nbr_cmd);
		}
	}
}
