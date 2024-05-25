/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:46:20 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/20 17:33:39 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	char			*d;
	char			*s;
	unsigned int	i;

	s = (char *)src;
	d = (char *)dest;
	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

/*int main()
{
    char str[50] = "GeeksForGeeks is for programming geeks.";
    char str2[10] = "test";
    printf("\nBefore memset(): %s\n", str);

    // Fill 8 characters starting from str[13] with '.'
    ft_memcpy(str + 13, str2, 4*sizeof(char));

    printf("After memset():  %s", str);
    return 0;
}*/
