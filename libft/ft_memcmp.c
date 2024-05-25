/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:18:14 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/23 12:47:43 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<string.h>
#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, unsigned int n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned int	i;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < (n - 1))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

/*int	main()
{
	char *str1 = "abcd";
	char *str2 = "aeCd";
	char *str3 = "abcd";
	int result;

	result = ft_memcmp(str1, str2, 2);
	printf("strcmp(str1, str2) = %d\n", result);
	result = ft_memcmp(str1, str3, 3);
	printf("strcmp(str1, str3) = %d\n", result);
	return 0;
}*/
