/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:16:11 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/06 14:35:18 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len,
		t_garbage **gc)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*c;

	s_len = ft_strlen(s);
	if (start > s_len)
	{
		len = 0;
	}
	else if (len > s_len - start)
		len = s_len - start;
	c = g_malloc(gc, (len + 1) * sizeof(char));
	if (c == 0)
		return (c);
	i = 0;
	while (i < len && s[i])
	{
		c[i] = s[start + i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
