/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ptr.c                                          :+:      :+:    :+:   */
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

//Linux only
//if (x == 0)
//	return ((t_fucknorm){"\0", 5, 0, 0, ft_max(data.width - 5, 0)});
static t_fucknorm	init_vars(unsigned long x, t_pfpd data)
{
	t_fucknorm	v;

	ft_bzero(v.fc, 4);
	if ((data.flags >> 1) & 1U)
		v.fc[0] = '+';
	else if ((data.flags >> 2) & 1U)
		v.fc[0] = ' ';
	*last(v.fc) = '0';
	*last(v.fc) = 'x';
	v.is = ulong_size(x, 16);
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

//Linux only
//if (x != 0)
//else
//	ft_strlcpy(last(res), "(nil)", 6);
char	*get_ptr(t_pfpd data, va_list va)
{
	char			*res;
	unsigned long	x;
	t_fucknorm		v;

	x = va_arg(va, unsigned long);
	v = init_vars(x, data);
	res = ft_calloc(v.pad_ + v.fcs + v.pad0 + v.is + 1, 1);
	if (res == NULL)
		return (NULL);
	ft_memset(res, ' ', v.pad_ * !(data.flags & 1U));
	ft_strlcpy(last(res), v.fc, v.fcs + 1);
	ft_memset(last(res), '0', v.pad0);
	ft_append_ul(last(res), x, v.is, "0123456789abcdef");
	ft_memset(last(res), ' ', v.pad_ * (data.flags & 1U));
	return (res);
}
