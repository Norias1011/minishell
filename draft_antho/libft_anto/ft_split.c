/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:04:13 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/27 13:41:34 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nextstep(char c, char charset)
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

int	words_count(char *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (nextstep(str[i], charset) == 0 && nextstep(str[i +1], charset) == 1)
		{
			count++;
		}
		i++;
	}
	return (count);
}

void	words_copy(char *dest, char *src, char charset)
{
	int	i;

	i = 0;
	while (nextstep(src[i], charset) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	split_word(char *str, char charset, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (nextstep(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (nextstep(str[i + j], charset) == 0)
				j++;
			tab[k] = (char *)malloc(sizeof(char) * (j + 1));
			if (tab[k] == 0)
			{
				return ;
			}
			words_copy(tab[k], str + i, charset);
			i = i + j;
			k++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*c1;
	int		words;

	if (s == 0)
	{
		return (0);
	}
	c1 = (char *) s;
	words = words_count(c1, c);
	tab = (char **)malloc(sizeof(char *) * (words +1));
	if (tab == 0)
	{
		free(tab);
		return (0);
	}
	split_word(c1, c, tab);
	tab[words] = 0;
	return (tab);
}
