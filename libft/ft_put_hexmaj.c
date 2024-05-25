/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_heXmaj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:03:07 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/27 18:08:13 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdarg.h>
#include"libft.h"

int	ft_hex_lenmaj(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

int	ft_put_hexmaj(unsigned int num)
{
	int	i;

	i = 0;
	if (num >= 16)
	{
		ft_put_hexmaj(num / 16);
		ft_put_hexmaj(num % 16);
	}
	else
	{
		if (num <= 9)
		{
			ft_putchar(num + '0');
			i++;
		}
		else
			ft_putchar(num - 10 + 'A');
	}
	return (i);
}

int	ft_print_hexmaj(unsigned int num)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_put_hexmaj(num);
	return (ft_hex_lenmaj(num));
}
