/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:00:36 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/23 12:02:34 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t count)
{
	unsigned char	*d;
	unsigned int	i;

	d = str;
	i = 0;
	while (i < count)
	{
		*d = (unsigned char)c;
		d++;
		i++;
	}
	return (str);
}
