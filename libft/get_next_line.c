/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:46:20 by ajeandel          #+#    #+#             */
/*   Updated: 2024/03/05 02:08:45 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

void	add_to_stash(t_lis **stash, char *buffer, int size);
char	*get_line(t_lis *stash, int i, int j);
char	*get_next_line(int fd);
void	read_stash(int fd, t_lis **stash);
void	clean(t_lis **stash);

void	read_stash(int fd, t_lis **stash)
{
	char	*buff;
	int		reader;

	while (!newline(stash[fd]))
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return ;
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader <= 0)
		{
			free(buff);
			return ;
		}
		buff[reader] = '\0';
		add_to_stash(stash, buff, fd);
	}
}

void	add_to_stash(t_lis **stash, char *buffer, int fd)
{
	t_lis	*old;
	t_lis	*new;

	old = get_last(stash[fd]);
	new = malloc(sizeof(t_lis));
	if (new == NULL)
		return ;
	if (old == NULL)
		stash[fd] = new;
	else
		old->next = new;
	new->next = NULL;
	new->content = buffer;
}

char	*get_line(t_lis *stash, int i, int j)
{
	char	*line;
	int		len;

	len = malloc_line(stash);
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				line[j++] = stash->content[i];
				line[j] = '\0';
				return (line);
			}
			line[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	line[j] = '\0';
	return (line);
}

void	clean(t_lis **list)
{
	t_lis	*last;
	t_lis	*new;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(sizeof(char) * BUFFER_SIZE);
	new = malloc(sizeof(t_lis));
	if (NULL == buf || NULL == new)
		return ;
	last = get_last(*list);
	i = 0;
	k = 0;
	while (last->content[i] && last->content[i] != '\n')
		++i;
	while (last->content[i] && last->content[++i])
		buf[k++] = last->content[i];
	buf[k] = '\0';
	new->content = buf;
	new->next = NULL;
	dealloc(list, new, buf);
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_lis	*stash[4096];
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	read_stash(fd, stash);
	if (stash[fd] == NULL)
		return (NULL);
	line = get_line(stash[fd], i, j);
	clean(&stash[fd]);
	return (line);
}
