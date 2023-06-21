/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:22:57 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/21 19:11:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	read_flags(const char *str, t_pfpd *data)
{
	int	i;

	data->flags = 0;
	i = 0;
	while (ft_is_flag(str[i]) >= 0)
		data->flags |= 1U << ft_is_flag(str[i++]);
	return (i);
}

static int	read_width(const char *str, t_pfpd *data, va_list va)
{
	int	res;
	int	i;

	data->width = 0;
	i = 0;
	if (str[0] == '*')
	{
		data->width = va_arg(va, int);
		return (1);
	}
	while (str[i] == '0')
		i++;
	res = ft_atoi(&str[i]);
	data->width = res;
	while (res > 0)
	{
		res /= 10;
		i++;
	}
	return (i);
}

static int	read_preci(const char *str, t_pfpd *data, va_list va)
{
	int	res;
	int	i;

	data->precision = 0;
	i = 0;
	if (str[0] != '.')
		return (0);
	data->flags |= 1U << 6;
	if (str[1] == '*')
	{
		data->precision = va_arg(va, int);
		return (2);
	}
	while (str[i +1] == '0')
		i++;
	res = ft_atoi(&str[i +1]);
	data->precision = res;
	while (res > 0)
	{
		res /= 10;
		i++;
	}
	return (i + 1);
}

t_pfpd	ft_get_flags(const char *str, va_list va)
{
	t_pfpd	data;
	int		i;

	i = 1;
	i += read_flags(&str[i], &data);
	i += read_width(&str[i], &data, va);
	i += read_preci(&str[i], &data, va);
	data.specifier = str[i];
	if (in(data.specifier, "diuxX") && data.precision != 0)
		data.flags |= 1U << ft_is_flag('0');
	return (data);
}
