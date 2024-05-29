/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:48:20 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/23 12:02:47 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	charc;
	const char		*string;
	int				i;

	i = 0;
	string = s;
	charc = c;
	while (string[i] != '\0')
	{
		if (string[i] == charc)
		{
			return ((char *)&string[i]);
		}
		i++;
	}
	if (charc == '\0')
		return ((char *)&string[i]);
	return (0);
}
