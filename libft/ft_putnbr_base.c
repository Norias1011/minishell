/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:25:12 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/27 18:20:47 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include"libft.h"

int	ft_putnbr_len(unsigned long long nbr, char *base)
{	
	int	size;

	size = 0;
	while (nbr != 0)
	{
		nbr = nbr / ft_strlen(base);
		size++;
	}
	return (size);
}

void	ft_putnbr_base(unsigned long long nbr2, char *base)
{
	unsigned long long	len;

	len = ft_strlen(base);
	if (nbr2 >= len)
	{
		ft_putnbr_base(nbr2 / len, base);
		nbr2 = nbr2 % len;
	}
	if (nbr2 < len)
		write(1, &base[nbr2], 1);
}

/*int main()
{
	char *base;
	int nbr;

	base = "0123456789";
	nbr = 10;
	
	ft_putnbr_base(nbr, base);
}*/
