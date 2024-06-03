/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:39:13 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/31 15:39:29 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*get_last_token(t_token *stash)
{
	if (stash == NULL)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

void	add_token(t_token **token_lst, t_token *new_token)
{
	t_token	*last;

	last = get_last_token(*token_lst);
	if (last == NULL)
	{
		*token_lst = new_token;
	}
	else
	{
		last->next = new_token;
	}
}

t_token_lex	get_symbol(char *symbol) // check les diffrents symboles
{
	t_token_lex res;

	res = SYMBOL;
	if (symbol[0] == '-')
		res = DASH;
	if (symbol[0] == '\'')
		res = QUOTE;
	if (symbol[0] == '"')
		res = DOUBLEQUOTE;
	if (symbol[0] == '|')
		res = PIPE;
	if (symbol[0] == '<')
		res = L_ARROW;
	if (symbol[0] == '>')
		res = R_ARROW;
	if (symbol[0] == '$')
		res = DOLLAR;
	return (res);
}

int	is_metachar(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == '|')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '$')
		return (1);
	return (0);
}
