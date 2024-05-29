/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:59:29 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/23 12:03:41 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	unsigned int	i;

	string1 = (unsigned char *)str1;
	string2 = (unsigned char *)str2;
	i = 0;
	if (n < 1)
	{
		return (0);
	}
	while (string1[i] == string2[i] && i < (n - 1))
	{
		i++;
	}
	return (string1[i] - string2[i]);
}
