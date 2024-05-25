/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:22:14 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/29 14:27:56 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *))
{
	t_list	*new_list;
	t_list	*save;

	if (!l || !f || !d)
		return (0);
	new_list = ft_lstnew(f(l->content));
	if (!new_list)
		return (0);
	save = new_list;
	l = l->next;
	while (l)
	{
		new_list->next = ft_lstnew(f(l->content));
		if (!new_list->next)
		{
			ft_lstclear(&save, d);
			return (0);
		}
		new_list = new_list->next;
		l = l->next;
	}
	new_list->next = NULL;
	return (save);
}
