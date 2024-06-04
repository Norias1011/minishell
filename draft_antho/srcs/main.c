/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:08:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/04 17:17:08 by akinzeli         ###   ########.fr       */
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
/* loop de minishell avec la gestion des signaux ainsi que le parsing et l'execution*/
void	minishell_loop(t_minishell *minishell)
{
	print_prompt();
	while (1)
	{
		signal_handler();
		minishell->prompt = NULL;
		minishell->prompt = readline(get_pwd(minishell));
		signal_handler_bis();
		if (!minishell->prompt)
			clean_exit(minishell, EXIT_SUCCESS);
		if (input_user_parser(minishell) == false)
			clean_exit(minishell, EXIT_FAILURE);
		else
		{
			token(minishell, minishell->prompt, &minishell->token);
			minishell->cmds = token_to_commands(minishell->token);
			free(minishell->prompt);
			minishell->token = NULL;
			pipe_pipe(&minishell->cmds, minishell->env_s, minishell->env,
				minishell);
		}
	}
}
