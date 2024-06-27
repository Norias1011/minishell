/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:34:26 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/17 11:45:25 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_pipes(int (*fd)[2], int nbr_cmd)
{
	int	i;

	i = 0;
	while (i < nbr_cmd - 1)
	{
		if (pipe(fd[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	pid_error(pid_t *pid, int (*fd)[2], t_minishell *mini)
{
	perror("fork");
	g_free(&(mini->garbage), pid);
	g_free(&(mini->garbage), fd);
	exit(EXIT_FAILURE);
}

void	malloc_pipe(int (**fd)[2], pid_t **pid, int nbr_cmd, t_minishell *mini)
{
	*pid = g_malloc(&(mini->garbage), nbr_cmd * sizeof(pid_t));
	if (!pid)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	*fd = g_malloc(&(mini->garbage), (nbr_cmd) * sizeof(*fd));
	if (!fd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

void	close_unused_pipe(int i, int nbr_cmd, int (*fd)[2])
{
	int	j;

	j = 0;
	while (j < nbr_cmd - 1)
	{
		if (i != j)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		j++;
	}
}
