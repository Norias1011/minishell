/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:19:56 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/29 16:07:07 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdarg.h>
#include"libft.h"

int	is_valid(char c)
{
	if (c == 's' || c == 'u' || c == 'i'
		|| c == 'd' || c == 'x'
		|| c == 'X' || c == '%'
		|| c == 'p' || c == 'c')
		return (1);
	return (0);
}

int	get_type(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'd' || c == 'i')
		count = ft_print_int(va_arg(args, int));
	if (c == 's')
		count = ft_print_string(va_arg(args, char *));
	if (c == 'u')
		count = ft_print_unsigned_int(va_arg(args, unsigned int));
	if (c == 'x')
		count = ft_print_hex(va_arg(args, unsigned int));
	if (c == 'X')
		count = ft_print_hexmaj(va_arg(args, unsigned int));
	if (c == 'c')
		count = ft_print_char((char)va_arg(args, int));
	if (c == 'p')
		count = ft_print_pointeur(va_arg(args, void *));
	if (c == '%')
		count = ft_print_prcent();
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	params;
	int		i;
	int		count;

	va_start(params, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += get_type(str[i + 1], params);
			i++;
		}
		else
		{
			count ++;
			ft_putchar(str[i]);
		}
		i++;
	}
	va_end(params);
	return (count);
}
