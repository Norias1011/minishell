/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_coll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:04:01 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/11 15:51:17 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	g_free(t_garbage **head, void *value)
{
	t_garbage	*temp;
	t_garbage	*prev;

	temp = *head;
	prev = NULL;
	while (temp != NULL)
	{
		if (temp->value == value)
		{
			if (prev == NULL)
				*head = temp->next;
			else
				prev->next = temp->next;
			free(value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	g_clear_memory(t_garbage *head)
{
	t_garbage	*temp;

	while (head != NULL)
	{
		temp = head;
		free(head->value);
		head = head->next;
		free(temp);
	}
}

int	g_add(t_garbage **head, void *value)
{
	t_garbage	*new_item;

	new_item = (t_garbage *)malloc(sizeof(t_garbage));
	if (new_item == NULL)
		return (0);
	new_item->value = value;
	new_item->next = *head;
	*head = new_item;
	return (1);
}

void	*g_malloc(t_garbage **head, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		g_clear_memory(*head);
		*head = NULL;
	}
	if (!g_add(head, ptr))
	{
		g_clear_memory(*head);
		*head = NULL;
	}
	return (ptr);
}
