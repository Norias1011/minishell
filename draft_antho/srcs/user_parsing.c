/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:31:16 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/03 13:44:55 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	input_user_parser(t_minishell *minishell)
{
	if (!(minishell->prompt))
		return (false);
	add_history(minishell->prompt);
	return (true);
}
/* print the env variable if $ is called */
char	*dollar_sign(t_minishell *minishell, char *args)
{
	t_env	*tmp;

	tmp = minishell->env_s;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, args))
		{
			free(args);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return ("");
}
