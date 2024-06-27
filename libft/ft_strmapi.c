/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:18:24 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/06 14:29:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char),
		t_garbage **gc)
{
	unsigned int	i;
	char			*c;
	char			*result;
	int				size;

	if (s == 0)
		return (0);
	c = (char *)s;
	size = ft_strlen(c);
	result = g_malloc(gc, (size + 1) * sizeof(char));
	if (result == 0)
	{
		return (result);
	}
	i = 0;
	while (c[i] != '\0')
	{
		result[i] = (*f)(i, c[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
