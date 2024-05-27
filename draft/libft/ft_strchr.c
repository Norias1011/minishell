/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:20:42 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/28 13:28:13 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*d;
	int		i;

	d = (char *)s;
	i = 0;
	c = (unsigned char)c;
	while (d[i])
	{
		if (d[i] == c)
			return ((char *)&d[i]);
		i++;
	}
	if (d[i] == c)
		return ((char *)&d[i]);
	return (NULL);
}

/*int main ()
{
  char str[50] = "This is a sample string";
  char * pch;
  printf ("Looking for the 's' character in \"%s\"...\n",str);
  pch=ft_strchr(str,'s');
  printf ("found at : %s\n",pch);
  return 0;
}*/
