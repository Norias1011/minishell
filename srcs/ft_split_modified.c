/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_modified.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:04:13 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/25 14:52:42 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	words_count_md(char *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (nextstep_md(str[i], charset) == 0 && nextstep_md(str[i + 1],
				charset) == 1)
		{
			count++;
		}
		i++;
	}
	return (count);
}

void	words_copy_md(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	split_word_main(int *i, int *j, char charset, char *str)
{
	if (*i == 0)
	{
		while (nextstep_md(str[*i + *j], charset) == 0 && str[*i + *j] != '\0')
			*j += 1;
		if (nextstep_md(str[*i + *j], charset) == 1 && str[*i + *j] != '\0')
			*j += 1;
	}
	else if (nextstep_md(str[*i + *j], charset) == 1)
	{
		while (nextstep_md(str[*i + *j], charset) == 1 && str[*i + *j] != '\0')
			*j += 1;
		while (nextstep_md(str[*i + *j], charset) == 0 && str[*i + *j] != '\0')
			*j += 1;
	}
	else if (nextstep_md(str[*i + *j], charset) == 0)
	{
		while (nextstep_md(str[*i + *j], charset) == 0 && str[*i + *j] != '\0')
			*j += 1;
	}
}

void	split_word_md(char *str, char charset, char **tab, t_garbage **gc)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		if ((nextstep_md(str[i], charset) == 1) && (str[i + 1] != '\0')
			&& nextstep_md(str[i + 1], charset) == 0)
			i++;
		split_word_main(&i, &j, charset, str);
		tab[k] = g_malloc(gc, (j + 1) * sizeof(char));
		if (tab[k] == 0)
			return ;
		words_copy_md(tab[k], str + i, j);
		i = i + j;
		k++;
	}
}

char	**ft_split_modified(char const *s, char c, t_garbage **gc)
{
	char	**tab;
	char	*c1;
	int		words;

	if (s == 0)
	{
		return (0);
	}
	c1 = (char *)s;
	words = words_count_md(c1, c);
	tab = g_malloc(gc, (words + 1) * sizeof(char *));
	if (tab == 0)
	{
		free(tab);
		return (0);
	}
	split_word_md(c1, c, tab, gc);
	tab[words] = 0;
	return (tab);
}
