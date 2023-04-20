/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:48:16 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/17 16:01:45 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*get_char(t_pfpd data, va_list va)
{
	char	*res;
	char	c;

	c = va_arg(va, int);
	res = ft_calloc(data.width + 1 + 1, 1);
	if (res == NULL)
		return (NULL);
	if ((data.flags >> 0) & 1U)
	{
		res[0] = c;
		ft_memset(&res[1], ' ', data.width - 1);
	}	
	else
	{
		ft_memset(res, ' ', data.width - 1);
		*last(res) = c;
	}
	return (res);
}

char	*get_perc(t_pfpd data, va_list va)
{
	char	*res;
	char	c;

	(void) va;
	c = '%';
	res = ft_calloc(data.width + 1 + 1, 1);
	if (res == NULL)
		return (NULL);
	if ((data.flags >> 0) & 1U)
	{
		res[0] = c;
		ft_memset(&res[1], ' ', data.width - 1);
	}	
	else
	{
		ft_memset(res, ' ', data.width - 1);
		*last(res) = c;
	}
	return (res);
}
