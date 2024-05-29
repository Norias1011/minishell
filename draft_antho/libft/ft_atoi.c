/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:32:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/23 11:48:05 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	char	*c;
	int		i;
	int		number;
	int		parity;

	c = (char *)str;
	i = 0;
	number = 0;
	parity = 1;
	while ((c[i] >= 9 && c[i] <= 13) || c[i] == 32)
		i++;
	if (c[i] == '+' || c[i] == '-')
	{
		if (c[i] == '-')
			parity = -1;
		i++;
	}
	while (c[i] >= '0' && c[i] <= '9')
	{
		number = number * 10;
		number = number + c[i] - '0';
		i++;
	}
	return (number * parity);
}
