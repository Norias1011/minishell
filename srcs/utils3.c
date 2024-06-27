/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:03:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/10 10:24:32 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_status_quote(t_minishell *mini, int *i, char **string)
{
	char	*word;

	word = NULL;
	word = g_malloc(&(mini->garbage), sizeof(char)
			* (ft_strlen(ft_itoa(mini->error, &(mini->garbage))) + 1));
	ft_strlcpy(word, ft_itoa(mini->error, &(mini->garbage)),
		ft_strlen(ft_itoa(mini->error, &(mini->garbage))) + 1);
	*i += 2;
	*string = ft_strjoin(*string, word, &(mini->garbage));
}

void	pid_handler(int i, pid_t *pid, int (*fd)[2], t_minishell *mini)
{
	pid[i] = fork();
	if (pid[i] < 0)
		pid_error(pid, fd, mini);
}

int	echo_n_loop(t_cmds *cmd_lst, int i)
{
	int	j;

	if (cmd_lst->args[i] != '\0' && cmd_lst->args[i] == ' '
		&& (strncmp(cmd_lst->args + (i + 1), "-n", 2) == 0))
		i++;
	while (((cmd_lst->args[i] != '\0') && (strncmp(cmd_lst->args + i, "-n",
					2) == 0)) && ((cmd_lst->args[i + 2] == ' ')
			|| cmd_lst->args[i + 2] == '\0' || (cmd_lst->args[i + 2] == 'n')))
	{
		j = 2;
		while (cmd_lst->args[i + j] != '\0' && cmd_lst->args[i + j] == 'n')
			j++;
		if (cmd_lst->args[i + j] != '\0' && cmd_lst->args[i + j] != ' ')
		{
			return (i);
		}
		else
			i = i + j + 1;
	}
	return (i);
}

int	nextstep_md(char c, char charset)
{
	if (c == charset)
	{
		return (1);
	}
	if (c == '\0')
	{
		return (1);
	}
	return (0);
}

void	set_cmd_null(t_cmds *new)
{
	new->args = NULL;
	new->next = NULL;
	new->command = NULL;
	new->file = NULL;
}
