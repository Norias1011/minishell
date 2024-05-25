/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:19:04 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/27 17:51:09 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdarg.h>
#include"libft.h"

int	ft_print_int(int nb)
{
	char	*str;
	int		len;

	str = ft_itoa(nb);
	if (str == NULL)
		return (0);
	len = ft_strlen((char *)str);
	write(1, str, len);
	free(str);
	return (len);
}
