/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:34:26 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/31 15:35:42 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_handler(char *rl, t_token *new, int i)
{
	int	j;

	j = 0;
	while (rl[i + j] && rl[i + j] != rl[i - 1])
		j++;
	if (i + j == ft_strlen(rl) && rl[i + j] != rl[i - 1])
		return (-1);
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
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
		new->token = QUOTE_STRING;
	}
	return (j);
}

int	check_arrow(char *rl, t_token *new, int i)
{
	if (new->token == L_ARROW && rl[i] == '<')
	{
		new->content = malloc(sizeof(char) * (3));
		if (!new->content)
		{
			free(new);
			return (0);
		}
		ft_strlcpy(new->content, rl + i - 1, 3);
		new->token = L_D_ARROW;
		return (1);
	}
	if (new->token == R_ARROW && rl[i] == '>')
	{
		new->content = malloc(sizeof(char) * (3));
		if (!new->content)
		{
			free(new);
			return (0);
		}
		ft_strlcpy(new->content, rl + i - 1, 3);
		new->token = R_D_ARROW;
		return (1);
	}
	return (0);
}

int	check_dollar(t_minishell *minishell, char *rl, t_token *new, int i)
{
	int	j;
	char	*tmp_string;
	t_env	*tmp;

	tmp = minishell->env_s;
	j = 0;
	i++;
	while (ft_isalpha(rl[i + j]) || ft_isdigit(rl[i + j]))
		j++;
	tmp_string = malloc(sizeof(char) * j);
	ft_strlcpy(tmp_string, rl + i - 1, j + 2);
	new->content = ft_strdup("");
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, tmp_string))
		{
			free(new->content);
			new->content = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
	return (j + 1);
}

/*void	dollar_quote(t_minishell *minishell, char *str)
{
	int	i;
	int	j;
	char	string;
	t_env	*tmp;
	
	i = 0;
	while (str[i])
	{
		j = 0;
		tmp = minishell->env_s;
		if (str[i] == '$')
		{
			while (ft_isalpha(str[i + j]) || ft_isdigit(str[i + j]))
				j++;
			ft_strlcpy(string, str + i, j);
			dollar_sign(minishell, string);
			while (x < j)
			{
				str[i] = str[i + x];
				x++;
			}
		}
		i++;
	}
}*/

void	token(t_minishell *minishell, char *rl, t_token **token_lst)
{
	int		i;
	int		add;
	t_token	*new;

	i = 0;
	add = 0;
	while (rl[i])
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return ;
		if ((ft_isalpha(rl[i]) || ft_isdigit(rl[i]))
			|| (is_metachar(rl[i]) == 0))
			add = token_string(rl, new, i);
		else if (rl[i] == ' ')
			add = token_space(rl, new, i);
		else
			add = token_symbol(rl, new, i);
		new->next = NULL;
		i += add;
		if ((new->token == QUOTE || new->token == DOUBLEQUOTE))
		{
			add = quote_handler(rl, new, i);
			if (add != -1)
			{
				i += add + 1;
				//dollar_quote(minishell, new->content);
				add_token(token_lst, new);
			}
			else
				add_token(token_lst, new);
			continue ;
		}
		if (new->token == L_ARROW || new->token == R_ARROW)
		{
			add = check_arrow(rl, new, i);
			i += add;
		}
		if (new->token == DOLLAR && (ft_isalpha(rl[i]) || ft_isdigit(rl[i])))
		{
			add = check_dollar(minishell, rl, new, i);
			i += add;
		}
		add_token(token_lst, new);
	}
}
