/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:27:45 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/22 14:18:42 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*d;

	d = (char *)s;
	i = 0;
	c = (unsigned char)c;
	while (d[i])
		i++;
	while (i >= 0)
	{
		if (d[i] == c)
			return ((char *)&d[i]);
		i--;
	}
	d = NULL;
	return (d);
}

/*int main ()
{
  char str[] = "This is a sample string";
  char * pch;
  pch=ft_strrchr(str,'s');
  printf ("Last occurence of 's' found at : %s\n",pch);
  return 0;
}*/
