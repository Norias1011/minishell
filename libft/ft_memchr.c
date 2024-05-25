/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:34:48 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/23 12:53:24 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<string.h>
#include "libft.h"

/*void	*ft_memchr(const void *s, int c, unsigned int n)
{
	char			*d;
	unsigned int	i;

	d = (char *)s;
	i = 0;
	c = (char)c;
	if ((c == 0 && n == 0) || c > ft_strlen(s))
		return (NULL);
	while (i < n && d[i])
	{
		if (d[i] == c)
		{
			return ((char *)&d[i]);
		}
		i++;
	}
	if (d[i] == c)
		return ((char *)&d[i]);
	return (NULL);
}*/

void	*ft_memchr(const void *s, int c, unsigned int n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (NULL);
}

/*int main ()
{
  char str[50] = "This is a sample string";
  char * pch;
  printf ("Looking for the 's' character in \"%s\"...\n",str);
  pch= ft_memchr(str,'s', 10);
  printf ("found at : %s\n",pch);
  return 0;
}*/
