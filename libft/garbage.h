/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:57:50 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/11 15:51:08 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include <stdlib.h>

typedef struct s_garbage
{
	void				*value;
	struct s_garbage	*next;
}						t_garbage;

void					*g_malloc(t_garbage **head, size_t size);
void					g_free(t_garbage **head, void *value);
void					g_clear_memory(t_garbage *head);
int						g_add(t_garbage **head, void *value);

#endif