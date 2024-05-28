/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:05:31 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/23 10:55:17 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned char	*c;
	unsigned char	*d;
	unsigned int	i;
	unsigned int	j;

	c = (unsigned char *)big;
	d = (unsigned char *)little;
	i = 0;
	j = 0;
	if (d[i] == 0)
		return ((char *)c);
	while (i < len && c[i] != '\0')
	{
		while (d[j] == c[i + j])
		{
			if (i + j < len)
			{
				if (d[j +1] == '\0')
					return ((char *)&c[i]);
			}
			j++;
		}
		i++;
	}
	return (0);
}
