/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:13 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/11 15:52:25 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_exit(t_minishell *minishell, int exno)
{
	minishell->error = exno;
	rl_clear_history();
	free_all(minishell);
	exit(exno);
}

void	free_all(t_minishell *minishell)
{
	g_clear_memory(minishell->garbage);
}
