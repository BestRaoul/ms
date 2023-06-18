/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:11:31 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/21 21:21:33 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	write_str(char *s, t_pfpd data)
{
	int	i;

	(void) data;
	i = 0;
	while (s[i] || (data.specifier == 'c' && (i < data.width || i == 0)))
	{
		if (write(1, &s[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

char	*get_format(t_pfpd data, va_list va)
{
	char	s;

	s = data.specifier;
	if (s == '%')
		return (get_perc(data, va));
	if (s == 'c')
		return (get_char(data, va));
	if (s == 's')
		return (get_str(data, va));
	if (s == 'd' || s == 'i')
		return (get_int(data, va));
	if (s == 'u')
		return (get_uint(data, va));
	if (s == 'p')
		return (get_ptr(data, va));
	if (s == 'x' || s == 'X')
		return (get_hex(data, va));
	return (NULL);
}

static int	write_format(const char *str, va_list va, int *i, int *res)
{
	t_pfpd	data;
	void	*out;
	int		j;

	j = *i + 1;
	while (str[j] && !ft_is_specifier(str[j]))
		j++;
	if (ft_is_specifier(str[j]))
	{
		data = ft_get_flags(&str[*i], va);
		out = get_format(data, va);
		if (out == NULL)
			return (-1);
		*res += write_str(out, data);
		FREE(out);
		*i = j;
		return (*res);
	}
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	va;
	int		i;
	int		res;

	va_start(va, format);
	i = 0;
	res = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (write_format(format, va, &i, &res) == -1)
				return (-1);
		}
		else if (write(1, &format[i], 1) == -1)
			return (-1);
		else
			res++;
		i++;
	}
	va_end(va);
	return (res);
}
