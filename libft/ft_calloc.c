/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:31:30 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/23 13:38:40 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char			*str;
	unsigned int	i;

	if (size == 0 || nitems == 0)
		return (malloc(1));
	if ((int)size < 0 || (int)nitems < 0)
		return (NULL);
	i = 0;
	str = (char *)malloc(nitems * size);
	if (str == NULL)
		return (NULL);
	while (i < size * nitems)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
