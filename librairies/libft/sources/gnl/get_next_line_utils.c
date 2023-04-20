/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:26:51 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/23 14:26:53 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_realloc(t_bufobj *bufobj, ssize_t new_len)
{
	ssize_t	i;
	char	*ptr;
	char	*dest;

	dest = malloc(new_len);
	if (dest == NULL)
	{
		if (bufobj->buf_allocated)
			free(bufobj->buf);
		return (0);
	}
	i = 0;
	ptr = bufobj->buf;
	while (i < bufobj->buf_size)
	{
		*(dest + i) = *(ptr + i);
		i ++;
	}
	if (bufobj->buf_allocated)
		free(bufobj->buf);
	bufobj->buf = dest;
	bufobj->buf_allocated = 1;
	return (1);
}
