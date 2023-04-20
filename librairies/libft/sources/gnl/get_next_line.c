/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:26:32 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/23 14:26:35 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

ssize_t	ioc(char c, t_bufobj *bufobj)
{
	ssize_t	i;

	i = 0;
	while (bufobj->buf && bufobj->buf_size > 0
		&& bufobj->buf_allocated && i < bufobj->buf_size)
	{
		if (bufobj->buf[i] == (const char)c)
			return (i);
		i ++;
	}
	return (-1);
}

void	init_bufobj(t_bufobj *bufobj)
{
	bufobj->eof = 0;
	if (bufobj)
		return ;
	bufobj->buf = 0;
	bufobj->buf_size = 0;
	bufobj->buf_allocated = 0;
}

int	handle_readsize(t_bufobj *bufobj, ssize_t readsize)
{
	if (readsize > 0)
		return (0);
	if (readsize == 0)
		bufobj->eof = 1;
	if (readsize == -1 || bufobj->buf_size == 0)
	{
		if (bufobj->buf_allocated && bufobj->buf)
		{
			free(bufobj->buf);
			bufobj->buf = NULL;
			bufobj->buf_size = 0;
			bufobj->buf_allocated = 0;
		}
		return (1);
	}
	return (0);
}

char	*gnl_2(t_bufobj *bufobj)
{
	char			*res;

	res = malloc(bufobj->index_of_nl + 2 - bufobj->eof);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, bufobj->buf, bufobj->index_of_nl + 1 - bufobj->eof);
	res[bufobj->index_of_nl + 1 - bufobj->eof] = 0;
	bufobj->new_buf_size
		= bufobj->buf_size - (bufobj->index_of_nl + 1 - bufobj->eof);
	bufobj->tmp = malloc(bufobj->new_buf_size);
	ft_memcpy(bufobj->tmp, bufobj->buf + bufobj->index_of_nl + 1 - bufobj->eof,
		bufobj->new_buf_size);
	if (bufobj->buf_allocated)
	{
		free(bufobj->buf);
		bufobj->buf_allocated = 0;
	}
	bufobj->buf = bufobj->tmp;
	bufobj->buf_size = bufobj->new_buf_size;
	bufobj->buf_allocated = 1;
	return (res);
}

char	*get_next_line(int fd)
{
	static t_bufobj	bufobj[4096];
	ssize_t			readsize;

	if (fd < 0 || fd > 4095)
		return (NULL);
	init_bufobj(&(bufobj[fd]));
	while (ioc('\n', &(bufobj[fd])) == -1 && !bufobj[fd].eof)
	{
		if (!gnl_realloc(&(bufobj[fd]), bufobj[fd].buf_size + BUFFER_SIZE))
			return (NULL);
		readsize = read(fd, bufobj[fd].buf + bufobj[fd].buf_size, BUFFER_SIZE);
		if (handle_readsize(&(bufobj[fd]), readsize))
			return (NULL);
		else
			bufobj[fd].buf_size += readsize;
	}
	bufobj[fd].index_of_nl = ioc('\n', &(bufobj[fd]));
	if (bufobj[fd].index_of_nl == -1)
		bufobj[fd].index_of_nl = bufobj[fd].buf_size;
	return (gnl_2(&(bufobj[fd])));
}
