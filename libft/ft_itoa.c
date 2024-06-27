/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:38:20 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/06 14:15:19 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(int number)
{
	long	num;

	num = number;
	if (num / 10 == 0)
	{
		return (1);
	}
	return (1 + count(num / 10));
}

char	*ft_itoa(int n, t_garbage **gc)
{
	long	size;
	long	num1;
	char	*result;

	num1 = n;
	size = count(num1);
	if (n < 0)
		size++;
	result = g_malloc(gc, (size + 1) * sizeof(char));
	if (result == 0)
		return (result);
	if (num1 < 0)
		num1 = num1 * -1;
	result[size--] = '\0';
	while (0 <= size)
	{
		result[size] = (num1 % 10) + '0';
		num1 = num1 / 10;
		size--;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
