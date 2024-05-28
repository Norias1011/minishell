/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:36:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/22 15:38:38 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char		*string;
	unsigned int		i;

	i = 0;
	string = (unsigned char *)str;
	while (i < n)
	{
		if (string[i] == (unsigned char)c)
		{
			return (&string[i]);
		}
		i++;
	}
	return (NULL);
}
