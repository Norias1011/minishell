/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:12:46 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/22 15:47:49 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char str, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == str)
			return (1);
		i++;
	}
	return (0);
}

int	first_position(char const *str, char const *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (check_set(str[i], set) == 1)
	{
		count++;
		i++;
	}
	return (count);
}

int	last_position(char const *str, char const *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (check_set(str[i], set) == 1)
	{
		i--;
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		len;
	int		start;

	if (s1 == 0)
		return (0);
	i = 0;
	start = first_position(s1, set);
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	len = last_position(s1, set) - first_position(s1, set);
	trim = malloc(sizeof(char) * (len + 1));
	if (trim == 0)
		return (0);
	while (i < len)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	return (trim);
}
