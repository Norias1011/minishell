/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:07:36 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/23 14:37:58 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

/*void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	const unsigned char	*c;
	unsigned char		*d;
	unsigned char		*temp;
	unsigned int		i;

	i = 0;
	c = src;
	d = dest;
	temp = dest;
	if (src == NULL)
		return (NULL);
	while (i < n)
	{
		temp[i] = c[i];
		i++;
	}
	temp[i] = '\0';
	i = 0;
	while (i < n)
	{
		d[i] = temp[i];
		i++;
	}
	return (d);
}*/

void	*ft_memmove(void *dst, const void *src, unsigned int n)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned int		i;

	s = src;
	d = dst;
	i = 0;
	if (src == NULL && dst == NULL)
		return (NULL);
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

/*#include <stdio.h>
#include <string.h>
int main()
{
	char str1[10] = "Geeks"; // Array of size 100
	char str2[10] = "Quiz"; // Array of size 5
	puts("str1 before memmove ");
	puts(str1);
	ft_memmove(str1 + 2, str2, 3);
	puts("\nstr1 after memmove ");
	puts(str1);
	return 0;
}*/
