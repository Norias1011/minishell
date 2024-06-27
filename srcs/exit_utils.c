/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:51:15 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/20 16:46:33 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
