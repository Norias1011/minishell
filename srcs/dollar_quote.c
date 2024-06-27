/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:34:26 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/21 18:13:10 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	path_quote(char *str, int *i, char **string, t_minishell *mini)
{
	char	*word;
	int		j;

	j = 0;
	word = NULL;
	while (str[(*i) + j] && (ft_isalpha(str[(*i) + j]) || ft_isdigit(str[(*i)
					+ j])))
		j++;
	if (j == 0)
		*i -= 1;
	word = g_malloc(&(mini->garbage), sizeof(char) * (j + 1));
	if (!word)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(word, str + *i, j + 1);
	word = dollar_sign(mini, word);
	*i += j;
	j = 0;
	if (word != NULL)
		*string = ft_strjoin(*string, word, &(mini->garbage));
}

void	malloc_str(char **str, int size, t_minishell *mini)
{
	*str = g_malloc(&(mini->garbage), sizeof(char) * (size + 1));
	if (!(*str))
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

char	*dollar_quote(t_minishell *m, char *str)
{
	int		i;
	char	*w;

	i = 0;
	w = NULL;
	malloc_str(&w, dollar_quote_length(m, str), m);
	w[0] = '\0';
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '\0' && str[i
				+ 1] != ' ')
		{
			if (str[i + 1] && str[i + 1] == '?')
				exit_status_quote(m, &i, &w);
			else
			{
				i++;
				path_quote(str, &i, &w, m);
			}
		}
		else
			help_dollar_quote(&i, &w, m, str);
	}
	return (w);
}

void	help_dollar_quote(int *i, char **w, t_minishell *m, char *str)
{
	*w = ft_strjoin(*w, ft_strndup(str + *i, 1, &(m->garbage)), &(m->garbage));
	*i += 1;
}

int	check_dollar2(t_minishell *m, int j, char *tmp_string, t_token *new)
{
	t_env	*tmp;

	tmp = m->env_s;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, tmp_string, 5))
		{
			g_free(&(m->garbage), new->content);
			new->content = ft_strdup(tmp->value, &(m->garbage));
			g_free(&(m->garbage), tmp_string);
			return (j);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*void	*dollar_quote_bis(char *str, char *w, int *i, t_minishell *m)
{
	if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != '\0' && str[*i
		+ 1] != ' ')
	{
		if (str[*i + 1] && str[*i + 1] == '?')
			exit_status_quote(m, i, &w);
		else
		{
			*i += 1;
			path_quote(str, i, &w, m);
		}
	}
	else
	{
		w = ft_strjoin(w, ft_strndup(str + *i, 1, &(m->garbage)),
				&(m->garbage));
		*i += 1;
	}
}*/

/* code de dollar_quote */
/*if (str[i] == '$' && str[i + 1] && str[i + 1] != '\0' && str[i
			+ 1] != ' ')
		{
			if (str[i + 1] && str[i + 1] == '?')
				exit_status_quote(m, &i, &w);
			else
			{
				i++;
				path_quote(str, &i, &w, m);
			}
		}
		else
		{
			w = ft_strjoin(w, ft_strndup(str + i, 1, &(m->garbage)),
					&(m->garbage));
			i++;
		}*/

/*w = ft_strjoin(w, ft_strndup(str + i, 1, &(m->garbage)),
					&(m->garbage));
			i++;*/
