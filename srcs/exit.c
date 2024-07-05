/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:29:37 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/05 14:03:07 by akinzeli         ###   ########.fr       */
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
		code_exit = check_exit(cmd_lst->args, minishell);
	if (code_exit == INT_MAX)
	{
		minishell->error = 1;
		return (0);
	}
	if (cmd_lst->args != NULL)
		printf("exit\n");
	clean_exit(minishell, code_exit);
	return (1);
}

int	pipe_exist(t_cmds *cmd_lst)
{
	if (cmd_lst && cmd_lst->next)
		return (1);
	return (0);
}

int	check_exit(char *str, t_minishell *minishell)
{
	int	i;
	int	code_exit;
	int	word;

	i = 0;
	code_exit = 0;
	word = count_word(str, ' ');
	while (str[i] != '\0' && word == 1)
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] == '+')
			i++;
		if ((str[i] < '0' || str[i] > '9') && (str[i] != '-'))
		{
			write(2, " numeric argument required\n", 27);
			clean_exit(minishell, 2);
		}
		i++;
	}
	if (word > 1)
		return (write(2, " too many arguments\n", 20), INT_MAX);
	code_exit = ft_atoi(str);
	code_exit = check_error_num(code_exit);
	return (code_exit);
}

int	check_error_num(int code_exit)
{
	if (code_exit < 0)
		return (256 + code_exit);
	if (code_exit > 255)
		return (code_exit % 256);
	return (code_exit);
}
