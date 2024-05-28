/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:08:25 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/26 12:05:16 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*info;

	info = (t_list *)malloc(sizeof(t_list));
	if (info == 0)
		return (0);
	info->content = content;
	info->next = NULL;
	return (info);
}
