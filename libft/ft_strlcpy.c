/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:32:40 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/22 15:45:28 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char const *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	x;

	i = 0;
	x = 0;
	while (src[x] != 0)
		x++;
	if (size < 1)
		return (x);
	while (src[i] != '\0' && (i < (size - 1)))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (x);
}
