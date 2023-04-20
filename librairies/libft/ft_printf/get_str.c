/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:48:16 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/17 16:01:45 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

//this ugly mess at the bottom is because of the norm, else i would commit /
//the heinous crime of a 26 line long method, god forbid!!
//Linux only
//strl = !(str == NULL && ((data.flags >> 6) & 1U && data.precision < 6));
char	*get_str(t_pfpd data, va_list va)
{
	char	*str;
	char	*res;
	int		padl;
	int		strl;

	str = va_arg(va, char *);
	strl = 1;
	if (str == NULL)
		str = ("(null)\0");
	strl = strl * ft_max(ft_min(data.precision, ft_strlen(str)),
			ft_strlen(str) * !((data.flags >> 6) & 1U));
	padl = ft_max(data.width - strl, 0);
	res = ft_calloc(strl + padl + 1, 1);
	if (res == NULL)
		return (NULL);
	if (!((data.flags >> 0) & 1U))
		ft_memset(res, ' ', padl);
	else
		ft_strlcpy(res, str, strl + 1);
	if (!((data.flags >> 0) & 1U))
		ft_strlcpy(&res[padl], str, strl + 1);
	else
		ft_memset(&res[strl], ' ', padl);
	return (res);
}
