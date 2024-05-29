/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:16:11 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/23 10:39:03 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
	c = (char *)malloc(sizeof(char) * (len + 1));
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
