/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:11:31 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/21 21:21:33 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

typedef struct s_fucknorm {
	t_pfpd	data;
	void	*out;
	int		j;
	int		len;
}	t_fucknorm;

static void	*ft_realloc(void *old, int old_size, int new_size)
{
	void	*new;

	new = MALLOC(new_size);
	if (new == NULL)
		return (NULL);
	if (old == NULL)
		return (new);
	ft_strlcpy(new, old, old_size);
	FREE(old);
	return (new);
}

static int	expand_format(char **format_ptr, va_list va, char **str, int *i)
{
	t_fucknorm	v;

	v.j = 1;
	while ((*format_ptr)[v.j] && !ft_is_specifier((*format_ptr)[v.j]))
		v.j++;
	if (ft_is_specifier((*format_ptr)[v.j]))
	{
		v.data = ft_get_flags(*format_ptr, va);
		v.out = get_format(v.data, va);
		if (v.out == NULL)
			return (-1);
		v.len = ft_strlen(v.out) * (v.data.specifier != 'c')
			+ v.data.width * (v.data.specifier == 'c');
		*str = ft_realloc(*str, *i, *i + v.len + 1);
		if (*str == NULL)
		{
			//CDO: return in one line
			FREE(v.out);
			return (-1);
		}
		ft_strlcpy(&(*str)[*i], v.out, v.len + 1);
		FREE(v.out);
		*i += v.len;
		*format_ptr += v.j;
		return (0);
	}
	return (-1);
}

typedef struct s_fucknorm2 {
	int		i;
	char	*format_ptr;
	char	*str;
}	t_fucknorm2;

char	*ft_allocprintf(const char *format, ...)
{
	va_list		va;
	t_fucknorm2	v;

	v = (t_fucknorm2){0, (char *)format, NULL};
	va_start(va, format);
	while (*v.format_ptr)
	{
		if (*v.format_ptr == '%' && expand_format(&v.format_ptr,
				va, &v.str, &v.i) == -1)
		{
			if (v.str != NULL)
				FREE(v.str);
			return (NULL);
		}
		else if (*v.format_ptr != '%')
		{
			v.str = ft_realloc(v.str, v.i, v.i + 2);
			if (v.str == NULL)
				return (NULL);
			v.str[v.i++] = *v.format_ptr;
		}
		v.format_ptr++;
	}
	v.str[v.i] = 0;
	return (va_end(va), v.str);
}

static int	add_format(char **format_ptr, va_list va, char **str)
{
	t_pfpd	data;
	void	*out;
	int		j;
	int		len;

	j = 1;
	while ((*format_ptr)[j] && !ft_is_specifier((*format_ptr)[j]))
		j++;
	if (ft_is_specifier((*format_ptr)[j]))
	{
		data = ft_get_flags(*format_ptr, va);
		out = get_format(data, va);
		if (out == NULL)
			return (-1);
		len = ft_strlen(out);
		if (data.specifier == 'c')
			len = data.width;
		ft_strlcpy(*str, out, len + 1);
		*str += len;
		FREE(out);
		*format_ptr += j;
		return (0);
	}
	return (-1);
}

char	*ft_yoloprintf(char *str, const char *format, ...)
{
	va_list	va;
	char	*format_ptr;	
	char	*start;

	start = str;
	format_ptr = (char *)format;
	va_start(va, format);
	while (*format_ptr)
	{
		if (*format_ptr == '%')
		{
			if (add_format(&format_ptr, va, &str) == -1)
				return (NULL);
		}
		else
			*(str++) = *format_ptr;
		format_ptr++;
	}
	*str = 0;
	va_end(va);
	return (start);
}
