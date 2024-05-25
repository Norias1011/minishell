/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:45:33 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/21 15:51:28 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<unistd.h>
#include"libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	c;

	c = '\0';
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (nb < 0)
		{
			nb = -nb;
			write(fd, "-", 1);
		}
		if (nb >= 10)
		{
			ft_putnbr_fd(nb / 10, fd);
			nb = nb % 10;
		}
		if (nb < 10)
		{
			c = nb + '0';
			write(fd, &c, 1);
		}
	}
}
