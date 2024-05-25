/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:47:25 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/26 11:48:29 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void	*content)
{
	t_list	*elt;

	elt = (t_list *)malloc(sizeof(*elt));
	if (elt == NULL)
		return (NULL);
	elt->content = content;
	elt->next = NULL;
	return (elt);
}
