/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:13:34 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/31 12:13:50 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void	handle_format(t_format *tf, va_list *ptr)
{
	if (tf->conversion == 'c')
		print_char(tf, va_arg(*ptr, int));
	else if (tf->conversion == 's')
		print_str(tf, va_arg(*ptr, char *));
	else if (tf->conversion == 'p')
		print_void_ptr(tf, va_arg(*ptr, void *));
	else if (tf->conversion == 'd' || tf->conversion == 'i')
		print_int(tf, va_arg(*ptr, int));
	else if (tf->conversion == 'u')
		print_unsigned(tf, va_arg(*ptr, unsigned int));
	else if (tf->conversion == 'x' || tf->conversion == 'X')
		print_hexadecimal(tf, va_arg(*ptr, unsigned int));
	else if (tf->conversion == '%')
		print_percent(tf);
}

void	handle_normal(const char **format_str, int *char_count)
{
	ft_putchar_fd_(**format_str, 1);
	(*char_count)++;
	(*format_str)++;
}

int	ft_printf(const char *format_str, ...)
{
	t_format	*tf;
	int			char_count;
	va_list		ptr;

	va_start(ptr, format_str);
	char_count = 0;
	while (*format_str)
	{
		if (*format_str == '%')
		{
			tf = build_format((char **)(&format_str));
			if (!tf)
				return (-1);
			handle_format(tf, &ptr);
			char_count += tf->chars_printed;
			free(tf);
		}
		else
			handle_normal(&format_str, &char_count);
	}
	va_end(ptr);
	return (char_count);
}
