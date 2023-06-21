/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_to_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_append_to_file(const char *fname, const char *content)
{
	int		fd;

	if (!content)
		return (0);
	fd = open(fname, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (0);
	if (ft_ptstrfd_s(content, fd) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
