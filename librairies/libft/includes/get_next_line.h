/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:26:41 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/23 14:26:42 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

typedef struct s_bufobj
{
	char	*buf;
	ssize_t	buf_size;
	int		eof;
	int		buf_allocated;
	ssize_t	index_of_nl;
	ssize_t	new_buf_size;
	char	*tmp;
}	t_bufobj;

int		gnl_realloc(t_bufobj *bufobj, ssize_t new_len);
size_t	gnl_strlen(const char *s);

#endif
