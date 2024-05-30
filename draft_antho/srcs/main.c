/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:08:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/30 04:03:00 by akinzeli         ###   ########.fr       */
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
	// char	**cmd;
	print_prompt();
	while (1)
	{
		signal_handler();
		minishell->prompt = readline("minishell$ > ");
		if (!minishell->prompt)
			clean_exit(minishell, EXIT_SUCCESS);
		if (input_user_parser(minishell) == false)
			clean_exit(minishell, EXIT_FAILURE);
		else
			continue ;
		/*cmd = ft_split(minishell->prompt, ' ');
		if (!cmd)
		{
			free(minishell->prompt);
			clean_exit(minishell, EXIT_FAILURE);
		}*/
		/*parse_cmd(cmd);
		free(line);
		free(cmd);*/
	}
}
