/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:48:12 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/26 12:09:03 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, char const *l, unsigned int n)
{
	unsigned int	len;
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	len = ft_strlen(l);
	if (n == 0 && !big)
		return (NULL);
	if ((int)n < 0)
		n = (unsigned int)ft_strlen(big);
	if (ft_strlen(l) == 0 || big == l)
		return ((char *)big);
	while (i < n && big[i])
	{
		c = 0;
		while (big[i + c] != '\0' && l[c] != '\0'
			&& big[i + c] == l[c] && i + c < n)
			c++;
		if (c == len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

/*int	main()
{
	char str1[20] = "abcdwfmkwamf";
	char str3[20] = "c";
	char *result;

	result = str1;
	result = ft_strnstr(str1, str3, 1);
	printf("strnstr(str1, str3) = %s\n", result);
	return 0;
}*/
