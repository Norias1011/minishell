/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:17:59 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/27 15:21:34 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdarg.h>
#include"libft.h"

int	ft_hex_len(unsigned int num)
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

int	ft_put_hex(unsigned int num)
{
	int	i;

	i = 0;
	if (num >= 16)
	{
		ft_put_hex(num / 16);
		ft_put_hex(num % 16);
	}
	else
	{
		if (num <= 9)
		{
			ft_putchar(num + '0');
			i++;
		}
		else
			ft_putchar(num - 10 + 'a');
	}
	return (i);
}

int	ft_print_hex(unsigned int num)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(num);
	return (ft_hex_len(num));
}
