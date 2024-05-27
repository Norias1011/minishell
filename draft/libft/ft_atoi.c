/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:13:31 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/23 10:38:36 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

int	ft_atoi(char const *str)
{
	int	i;
	int	res;
	int	j;

	i = 0;
	res = 0;
	j = 1;
	while ((str[i] == ' ' || str[i] == '\t')
		|| (str[i] == '\f' || str[i] == '\r')
		|| (str[i] == '\n' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -j;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * j);
}
/*int main()
{
	char *test;

	test = "      --++-5462ab4";
	printf("%d",ft_atoi(test));
}*/
