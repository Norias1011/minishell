/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:01 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/22 10:38:39 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdlib.h>
#include<stdio.h>
#include "libft.h"

int	isset(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	cutstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (isset(s1[i], set) == 1)
		i++;
	return (i);
}

int	cutend(char const *s1, char const *set)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	len--;
	while (isset(s1[len - i], set) == 1)
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	char	*res;

	i = 0;
	if (set == NULL)
		return ((char *)s1);
	if (s1 == NULL || ((ft_strlen(s1) == 1) && isset(s1[0], set)))
		return (NULL);
	len = ft_strlen(s1) - (cutstart(s1, set) + cutend(s1, set));
	if (cutstart(s1, set) == ft_strlen(s1))
		return (ft_strdup(""));
	res = (char *)malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = s1[cutstart(s1, set) + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
