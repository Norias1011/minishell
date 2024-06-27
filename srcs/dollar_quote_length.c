/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:34:26 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/17 11:45:55 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dollar_quote_length2(int *i, t_minishell *mini, int *x, char *str)
{
	int		j;
	char	*string;

	j = 1;
	if (str[*i + 1] == '?')
	{
		*x += ft_strlen(ft_itoa(mini->error, &(mini->garbage)));
		*i = *i + 1;
		return ;
	}
	while (str[*i + j] && (ft_isalpha(str[*i + j]) || ft_isdigit(str[*i + j])))
		j++;
	malloc_str(&string, j - 1, mini);
	string[0] = '\0';
	ft_strlcpy(string, str + *i, j);
	string = dollar_sign(mini, string);
	if (string != NULL)
		*x += ft_strlen(string);
	*i += j - 2;
}

int	dollar_quote_length(t_minishell *mini, char *str)
{
	int		i;
	int		x;
	char	*string;

	i = 0;
	x = 0;
	string = NULL;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '\0' && str[i
				+ 1] != ' ')
			dollar_quote_length2(&i, mini, &x, str);
		x++;
		i++;
	}
	free(string);
	return (x);
}
