/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:23:16 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/23 12:22:05 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdlib.h>
#include<stdio.h>
#include"libft.h"

int	issep(char c, char s)
{
	if (c == s || c == '\0')
		return (1);
	return (0);
}

void	copy_mot(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (issep(src[i], c) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

unsigned int	countword(char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (issep(s[i], c) == 0 && issep(s[i + 1], c) == 1)
			count++;
		i++;
	}
	return (count);
}

int	copy(char *s, char **res, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	mts;

	i = 0;
	j = 0;
	mts = 0;
	while (s[i])
	{
		if (issep(s[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (issep(s[i + j], c) == 0)
				j++;
			res[mts] = (char *)malloc(sizeof(char) * (j + 1));
			if (res[mts] == NULL)
				return (0);
			copy_mot(res[mts], s + i, c);
			i = i + j;
			mts++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		mots;

	if (s == NULL)
		return (NULL);
	mots = countword((char *)s, c);
	res = (char **)malloc(sizeof(char *) * (mots + 1));
	if (res == NULL)
		return (NULL);
	copy((char *)s, res, c);
	res[mots] = 0;
	return (res);
}

/*int	main()
{
	char	str[30] = "olol              ";
	char	sep = ' ';
	char **res;
	int i = 0;

	res = ft_split(str,sep);
	while (res[i])
	{
		printf("%s\n",res[i]);
		i++;
	}
}*/
