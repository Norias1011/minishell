/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:02:00 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/22 15:43:36 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*c;
	char	*d;
	int		i;

	d = (char *) s;
	i = 0;
	while (d[i] != '\0')
	{
		i++;
	}
	c = malloc(sizeof(char) * i +1);
	if (c == 0)
	{
		return (c);
	}
	i = 0;
	while (d[i] != '\0')
	{
		c[i] = d[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
