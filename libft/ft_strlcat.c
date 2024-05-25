/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:10:51 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/23 13:41:58 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <bsd/string.h>
#include "libft.h"

unsigned int	ft_strlcat(char *dest, char const *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[k] != 0)
		k++;
	while (dest[i] != 0)
		i++;
	if (size < 1)
		return (i);
	while (((j + i) < size - 1) && (src[j] != '\0'))
	{
		dest[i + j] = src[j];
		j++;
	}
	if ((i + j) < size)
		dest[i + j] = '\0';
	if (i > size)
		return (size + k);
	return (i + k);
}

/*int main ()
{
  char str[80]="test : ";
  unsigned int	taille;
  unsigned int	res;

  taille = 10;
  res = ft_strlcat(str,"this is a test",3);
  printf("%d\n",res);
  printf("%s",str);
  return 0;
}*/
