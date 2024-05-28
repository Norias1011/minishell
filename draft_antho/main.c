/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:08:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/28 15:10:48 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	(void)argc, (void)argv, (void)env;
	print_prompt();
	t_minishell *minishell;

	minishell = init_mini_shell(minishell, env);
	/*if (init_mini_shell() == -1)
		return (EXIT_FAILURE);*/
	// function init a faire pour init les variables de minishell

	// while (1)
	minishell->prompt = readline("minishell$ >");
	return (0);
}