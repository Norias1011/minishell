/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:08:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/28 17:20:40 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	(void)argc, (void)argv;
	print_prompt();
	t_minishell minishell;

	if (init_mini_shell(&minishell, env) == -1)
	{
		return (EXIT_FAILURE);
	}
	// while (1)
	minishell.prompt = readline("minishell$ >");
	return (0);
}