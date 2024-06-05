/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:29:37 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/05 23:28:00 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	int	pipe;
	int	code_exit;

	code_exit = 0;
	pipe = pipe_exist(cmd_lst);
	if (cmd_lst->args == NULL)
		printf("exit\n");
	if (pipe == 1 || cmd_lst->args == NULL)
		code_exit = errno;
	else
		code_exit = check_exit(cmd_lst->args);
	if (code_exit == 255 || code_exit == 1)
		return (0);
	clean_exit(minishell, code_exit);
	return (1);
}

int	pipe_exist(t_cmds *cmd_lst)
{
	if (cmd_lst && cmd_lst->next)
		return (1);
	return (0);
}

int	check_exit(char *str)
{
	int	i;
	int	code_exit;
	int	word;

	i = 0;
	code_exit = 0;
	word = count_word(str, ' ');
	if (word > 1)
		return (printf("exit: too many arguments\n"), 1);
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (printf("exit: %s: numeric argument required\n", str), 255);
		i++;
	}
	code_exit = ft_atoi(str);
	if (code_exit < 0)
		return (printf("minishell: exit: %s: numeric argument required\n", str),
			255);
	return (code_exit);
}

int	count_word(char *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (nextsteps(str[i], charset) == 0 && nextsteps(str[i + 1],
				charset) == 1)
		{
			count++;
		}
		i++;
	}
	return (count);
}

int	nextsteps(char c, char charset)
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
