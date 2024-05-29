/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:49:40 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/23 12:05:38 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*p;

	if (nitems == 0 || size == 0)
		return (malloc(1));
	if (nitems >= 2147483647 || size >= 2147483647
		|| nitems * size >= 2147483647)
		return (0);
	p = (void *)malloc(nitems * size);
	if (p == 0)
		return (p);
	ft_bzero(p, (nitems * size));
	return (p);
}
