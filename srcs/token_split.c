/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:39:44 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/06 16:00:55 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_string(char *rl, t_token *new, int i, t_minishell *minishell)
{
	int	j;

	j = 0;
	while ((rl[i + j]) && (is_metachar(rl[i + j]) == 0))
		j++;
	new->content = g_malloc(&(minishell->garbage), sizeof(char) * (j + 1));
	if (!new->content)
		return (0);
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = STRING;
	return (j);
}

int	token_space(char *rl, t_token *new, int i, t_minishell *minishell)
{
	int	j;

	j = 0;
	while (rl[i + j] == ' ')
		j++;
	if (rl[i + j] == '\0' || rl[i + j] == '|')
	{
		new->content = ft_strdup("", &(minishell->garbage));
		new->token = STRING;
		return (j);
	}
	new->content = ft_strdup(" ", &(minishell->garbage));
	new->token = SPC;
	return (j);
}

int	token_symbol(char *rl, t_token *new, int i, t_minishell *minishell)
{
	int	j;

	j = 1;
	new->content = g_malloc(&(minishell->garbage), sizeof(char) * (j + 1));
	if (!new->content)
		return (0);
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = get_symbol(new->content);
	return (j);
}

int	simple_token(char *rl, int i, t_token *new, t_minishell *mini)
{
	int	add;

	add = 0;
	if ((ft_isalpha(rl[i]) || ft_isdigit(rl[i]))
		|| (is_metachar(rl[i]) == 0))
		add = token_string(rl, new, i, mini);
	else if (rl[i] == ' ')
		add = token_space(rl, new, i, mini);
	else
		add = token_symbol(rl, new, i, mini);
	return (add);
}
