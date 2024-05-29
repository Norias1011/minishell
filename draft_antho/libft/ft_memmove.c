/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:18:32 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/23 12:24:22 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*src_char;
	char			*dest_char;

	if (!dest && !src)
		return (0);
	src_char = (char *) src;
	dest_char = (char *) dest;
	if (dest > src)
	{
		i = n - 1;
		while (i + 1 > 0)
		{
			dest_char[i] = src_char[i];
			i--;
		}
		return (dest);
	}
	i = 0;
	while (i < n)
	{
		dest_char[i] = src_char[i];
		i++;
	}
	return (dest);
}
