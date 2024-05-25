/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:01:15 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/22 15:39:24 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <bsd/string.h>
#include "libft.h"

int	ft_strncmp(char const *str1, char const *str2, unsigned int n)
{
	unsigned int		i;
	unsigned char		*s1;
	unsigned char		*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (n < 1)
		return (0);
	while (s1[i] == s2[i] && s1[i] && i < (n - 1))
		i++;
	return (s1[i] - s2[i]);
}

/*int	main()
{
	char *str1 = "abcdwfmkwamf";
	char *str3 = "jbcdedlkalwdk";
	int result;

	result = ft_strncmp(str1, str3, 0);
	printf("strncmp(str1, str3) = %d\n", result);
	return 0;
}*/
