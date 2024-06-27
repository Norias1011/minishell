/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:34:26 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/20 17:12:02 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_handler(t_minishell *mini, char *rl, t_token *new, int i)
{
	int	j;

	j = 0;
	while (rl[i + j] && rl[i + j] != rl[i - 1])
		j++;
	if ((i + j == ft_strlen(rl)) && (rl[i + j] != rl[i - 1]))
		return (-1);
	new->content = g_malloc(&(mini->garbage), sizeof(char) * (j + 1));
	if (!new->content)
	{
		perror("malloc");
		return (0);
	}
	if (j == 0 && rl[i] != ft_strlen(rl))
	{
		ft_strlcpy(new->content, " ", j + 1);
		new->token = SPC;
	}
	else
	{
		ft_strlcpy(new->content, rl + i, j + 1);
		if (new->content && new->token == DOUBLEQUOTE)
			new->content = dollar_quote(mini, new->content);
	}
	return (j);
}

int	check_arrow(char *rl, t_token *new, int i, t_minishell *mini)
{
	if (new->token == L_ARROW && rl[i] == '<')
	{
		new->content = g_malloc(&(mini->garbage), sizeof(char) * (3));
		if (!new->content)
			return (perror("malloc"), 0);
		ft_strlcpy(new->content, rl + i - 1, 3);
		new->token = L_D_ARROW;
		return (1);
	}
	if (new->token == R_ARROW && rl[i] == '>')
	{
		new->content = g_malloc(&(mini->garbage), sizeof(char) * (3));
		if (!new->content)
			return (perror("malloc"), 0);
		ft_strlcpy(new->content, rl + i - 1, 3);
		new->token = R_D_ARROW;
		return (1);
	}
	return (0);
}

int	check_dollar(t_minishell *m, char *rl, t_token *new, int i)
{
	int		j;
	int		check;
	char	*tmp_string;

	j = 0;
	while (ft_isalpha(rl[i + j]) || ft_isdigit(rl[i + j]))
		j++;
	tmp_string = g_malloc(&(m->garbage), sizeof(char) * j);
	tmp_string = ft_strndup(rl + i, j, &(m->garbage));
	new->content = ft_strdup("", &(m->garbage));
	if (j == 0 && rl[i] == '?')
	{
		new->content = ft_strdup(ft_itoa(m->error, &(m->garbage)),
				&(m->garbage));
		return (1);
	}
	check = check_dollar2(m, j, tmp_string, new);
	if (check != 0)
		return (check);
	while (rl[i + j] && rl[i + j] == ' ')
		j++;
	g_free(&(m->garbage), tmp_string);
	return (j);
}

void	handle_token_speciaux(int *i, t_token *new, char *rl, t_minishell *mini)
{
	int	add;

	add = 0;
	if (new->token == L_ARROW || new->token == R_ARROW)
	{
		add = check_arrow(rl, new, *i, mini);
		*i += add;
	}
	if (new->token && new->token == DOLLAR && (ft_isalpha(rl[*i])
			|| ft_isdigit(rl[*i]) || rl[*i] == '?'))
	{
		add = check_dollar(mini, rl, new, *i);
		*i += add;
	}
	if (new->token && (new->token == QUOTE || new->token == DOUBLEQUOTE))
	{
		add = quote_handler(mini, rl, new, *i);
		if (add != -1)
			*i += add + 1;
	}
}

void	token(t_minishell *mini, char *rl, t_token **token_lst)
{
	int		i;
	t_token	*new;

	i = 0;
	while (rl != NULL && rl[i])
	{
		new = g_malloc(&(mini->garbage), sizeof(t_token));
		if (!new)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		new->content = NULL;
		new->next = NULL;
		i += simple_token(rl, i, new, mini);
		handle_token_speciaux(&i, new, rl, mini);
		add_token(token_lst, new);
	}
}
