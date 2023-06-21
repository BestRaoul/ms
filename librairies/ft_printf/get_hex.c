/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:48:16 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/17 16:01:45 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

typedef struct s_fucknorm {
	char	fc[4];
	int		is;
	int		fcs;
	int		pad0;
	int		pad_;
}	t_fucknorm;

static t_fucknorm	init_vars(unsigned int x, t_pfpd data)
{
	t_fucknorm	v;

	ft_bzero(v.fc, 4);
	if (x > 0 && (data.flags >> 1) & 1U)
		v.fc[0] = '+';
	else if ((data.flags >> 2) & 1U)
		v.fc[0] = ' ';
	if (x > 0 && (data.flags >> 3) & 1U)
	{
		*last(v.fc) = '0';
		*last(v.fc) = data.specifier;
	}
	v.is = long_size(x, 16) - (x == 0 && data.precision == 0
			&& data.flags >> 6 & 1U && data.width > 0);
	v.fcs = ft_strlen(v.fc);
	v.pad0 = ft_max(data.precision - v.is, 0);
	v.pad_ = ft_max(data.width - v.fcs - v.pad0 - v.is, 0);
	if ((data.flags >> 4) & 1U && !((data.flags >> 6) & 1U) && v.pad0 == 0)
	{
		v.pad0 = v.pad_;
		v.pad_ = 0;
	}
	return (v);
}

char	*get_hex(t_pfpd data, va_list va)
{
	char			*res;
	unsigned int	x;
	t_fucknorm		v;

	x = va_arg(va, unsigned int);
	v = init_vars(x, data);
	res = ft_calloc(v.pad_ + v.fcs + v.pad0 + v.is + 1, 1);
	if (res == NULL)
		return (NULL);
	ft_memset(res, ' ', v.pad_ * !(data.flags & 1U));
	ft_strlcpy(last(res), v.fc, v.fcs + 1);
	ft_memset(last(res), '0', v.pad0);
	if (!(x == 0 && data.precision == 0 && (data.flags >> 6) & 1U))
	{
		if (data.specifier == 'x')
			ft_append_num(last(res), x, v.is, "0123456789abcdef");
		if (data.specifier == 'X')
			ft_append_num(last(res), x, v.is, "0123456789ABCDEF");
	}
	ft_memset(last(res), ' ', v.pad_ * (data.flags & 1U));
	return (res);
}
