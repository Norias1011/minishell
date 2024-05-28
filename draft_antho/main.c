/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:08:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/28 11:55:14 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	(void)argc, (void)argv, (void)env;
	t_minishell *minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->prompt = readline(print_prompt());
	return (0);
}