/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_int.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:24:18 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/27 18:03:19 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdarg.h>
#include"libft.h"

unsigned int	size_mot_unsigned(unsigned int n)
{
	unsigned int	size;

	size = 0;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char			*res;
	unsigned int	size;
	long			nbr;

	nbr = n;
	size = size_mot_unsigned(n);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (res == NULL)
		return (NULL);
	res[size--] = '\0';
	while (0 < size + 1)
	{
		res[size--] = ((nbr % 10) + '0');
		nbr = nbr / 10;
	}
	return (res);
}

int	ft_print_unsigned_int(unsigned int x)
{
	char	*str;
	int		len;

	if (x == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	str = ft_itoa_unsigned(x);
	if (str == NULL)
		return (0);
	len = ft_strlen((char *)str);
	write(1, str, len);
	free(str);
	return (len);
}
