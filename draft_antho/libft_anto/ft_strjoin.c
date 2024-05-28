/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:48:15 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/22 15:44:22 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(char const *str);
/*{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}*/

char	*ft_strjoin2(char const *c1, char const *c2, char *result1)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (c1[i] != '\0')
	{
		result1[k] = c1[i];
		k++;
		i++;
	}
	while (c2[j] != '\0')
	{
		result1[k] = c2[j];
		k++;
		j++;
	}
	result1[k] = '\0';
	return (result1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		size1;
	int		size2;

	if (s1 == 0 || s2 == 0)
		return (0);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	if (result == 0)
		return (0);
	ft_strjoin2(s1, s2, result);
	return (result);
}
