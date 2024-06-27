/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:02:00 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/11 15:55:04 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, t_garbage **gc)
{
	size_t	s_len;
	char	*dest;

	s_len = ft_strlen(s) + 1;
	dest = g_malloc(gc, s_len);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, s_len);
	return (dest);
}

/*char	*ft_strdup(const char *s, t_garbage **gc)
{
	char	*c;
	char	*d;
	size_t	i;

	d = (char *)s;
	i = 0;
	while (d[i] != '\0')
	{
		i++;
	}
	c = g_malloc(gc, (i + 1) * sizeof(char));
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
}*/