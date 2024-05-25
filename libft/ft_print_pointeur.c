/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointeur.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:29:42 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/27 17:58:34 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"libft.h"

int	ft_print_pointeur(void *adr)
{
	unsigned long long	temp;
	char				*base;
	int					len;

	base = "0123456789abcdef";
	temp = (unsigned long long)adr;
	if (temp == 0)
	{
		ft_print_string("(nil)");
		return (5);
	}
	write(1, "0x", 2);
	ft_putnbr_base(temp, base);
	len = ft_putnbr_len(temp, base);
	return (len + 2);
}
