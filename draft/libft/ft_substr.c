/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:26:17 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/26 12:25:08 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include "libft.h"

/*char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((int)start > ft_strlen(s))
		len = 0;
	if ((int)len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	while (i < len && ((start + i) < (unsigned int)ft_strlen(s)))
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	while (start < (unsigned int)ft_strlen(s) && i < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	size_t	size;
	char	*tab;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	tab = (char *)malloc((len + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	count = 0;
	while (count < len)
	{
		tab[count] = s[start + count];
		count++;
	}
	tab[count] = '\0';
	return (tab);
}
