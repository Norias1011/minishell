/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:57:47 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/28 15:13:26 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_mini_shell(t_minishell *minishell, char **env)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	if (!init_env(minishell, env))
	{
		printf("Error: init_env failed\n");
		return (0);
	}
	// init working directory
	// init le reste
	return (1);
}