/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:48:13 by ajeandel          #+#    #+#             */
/*   Updated: 2024/03/05 02:09:13 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libft.h"

void	*ft_calloc(size_t nitems, size_t size);
t_lis	*get_last(t_lis *stash);
int		newline(t_lis *stash);
int		malloc_line(t_lis *stash);

void	dealloc(t_lis **list, t_lis *clean, char *buf)
{
	t_lis	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean->content[0])
		*list = clean;
	else
	{
		free(buf);
		free(clean);
	}
}

t_lis	*get_last(t_lis *stash)
{
	if (stash == NULL)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

int	newline(t_lis *stash)
{
	int	i;

	if (stash == NULL)
		return (0);
	while (stash)
	{
		i = 0;
		while (stash->content[i] && i < BUFFER_SIZE)
		{
			if (stash->content[i] == '\n')
				return (1);
			i++;
		}
		stash = stash->next;
	}
	return (0);
}

int	malloc_line(t_lis *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		stash = stash->next;
	}
	return (len);
}
