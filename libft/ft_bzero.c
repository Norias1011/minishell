/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:16:45 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/19 16:06:29 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include "libft.h"

void	ft_bzero(void *str, unsigned int n)
{
	char			*d;
	unsigned int	i;

	d = str;
	i = 0;
	while (i < n)
	{
		d[i] = '\0';
		i++;
	}
}

/*int main()
{
    char str[50] = "GeeksForGeeks is for programming geeks.";
    printf("\nBefore memset(): %s\n", str);

    // Fill 8 characters starting from str[13] with '.'
    ft_bzero(str + 13, 8*sizeof(char));

    printf("After memset():  %s", str);
    return 0;
}*/
