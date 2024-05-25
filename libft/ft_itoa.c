/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:02:59 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/23 12:45:09 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include "libft.h"

int	size_mot(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		size;
	long	nbr;

	nbr = n;
	size = size_mot(n);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (res == NULL)
		return (NULL);
	if (nbr < 0)
		nbr = nbr * -1;
	res[size--] = '\0';
	while (0 <= size)
	{
		res[size] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		size--;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
