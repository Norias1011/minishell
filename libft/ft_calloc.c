/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:49:40 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/06 14:12:17 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size, t_garbage **gc)
{
	void	*p;
	size_t	total_size;

	total_size = nitems * size;
	if (nitems == 0 || size == 0)
		return (malloc(1));
	if (nitems >= 2147483647 || size >= 2147483647 || nitems
		* size >= 2147483647)
		return (0);
	p = g_malloc(gc, total_size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, (nitems * size));
	return (p);
}
