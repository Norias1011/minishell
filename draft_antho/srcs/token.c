/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:39:44 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/31 15:40:09 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_string(char *rl, t_token *new, int i)
{
	int	j;

	j = 0;
	while ((rl[i + j]) && (is_metachar(rl[i + j]) == 0))
		j++;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = STRING;
	return (j);
}

int	token_space(char *rl, t_token *new, int i)
{
	int	j;

	j = 0;
	while (rl[i + j] == ' ')
		j++;
	new->content = ft_strdup(" ");
	new->token = SPC;
	return (j);
}

int	token_symbol(char *rl, t_token *new, int i)
{
	int j;

	j = 1;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = get_symbol(new->content);
	return (j);
}
