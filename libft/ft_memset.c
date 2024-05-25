/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:22:29 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/20 17:26:40 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<unistd.h>
#include "libft.h"

void	*ft_memset(void *str, int c, unsigned int n)
{
	unsigned int	i;
	unsigned char	*d;

	d = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		d[i] = c;
		i++;
	}
	return (d);
}

/*int main()
{
    char str[50] = "GeeksForGeeks is for programming geeks.";
    printf("\nBefore memset(): %s\n", str);

    // Fill 8 characters starting from str[13] with '.'
    ft_memset(str + 13, '.', 8*sizeof(char));

    printf("After memset():  %s", str);
    return 0;
}*/
