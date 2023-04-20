/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadecimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:47:06 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/10 16:47:07 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

size_t	hex_width(t_format *t, unsigned int n)
{
	size_t	res;

	res = unsigned_num_width_size_t(n, 16);
	if (t->flags[2] && n > 0)
		res += 2;
	return (res);
}

void	handle_width_one(t_format *t, size_t n, size_t final_len,
	size_t prec_len)
{
	if (t->flags[2] && n > 0)
	{
		if (t->conversion == 'x')
			count_put_str("0x", t);
		else
			count_put_str("0X", t);
		if (t->precision + 2 > hex_width(t, n))
			print_zeroes(prec_len, t);
	}
	else
	{
		if (t->precision > hex_width(t, n))
			print_zeroes(prec_len, t);
	}
	t->chars_printed += (int)unsigned_num_width_size_t(n, 16);
	put_hex_fd(n, t->conversion == 'X', 0, 1);
	print_blanks((t->width) - final_len, t);
}

void	handle_width_two(t_format *t, size_t n, size_t final_len,
	size_t prec_len)
{
	if (!t->flags[1])
		print_blanks((t->width) - final_len, t);
	if (t->flags[2] && n > 0)
	{
		if (t->conversion == 'x')
			count_put_str("0x", t);
		else
			count_put_str("0X", t);
		if (t->precision + 2 > hex_width(t, n))
			print_zeroes(prec_len, t);
	}
	if (t->flags[1])
		print_zeroes((t->width) - final_len, t);
	if (!t->flags[2] && t->precision > hex_width(t, n))
		print_zeroes(prec_len, t);
	t->chars_printed += (int)unsigned_num_width_size_t(n, 16);
	put_hex_fd(n, t->conversion == 'X', 0, 1);
}

void	handle_init(size_t n, t_format *t, size_t *final_len, size_t *prec_len)
{
	if (n == 0)
		t->flags[2] = 0;
	if (t->flags[2] && n > 0)
		*prec_len += 2;
	if (((t->precision + t->flags[2] * 2)) > *final_len)
		*final_len += *prec_len;
	if (t->flags[3] || t->flags[4])
		(*final_len)++;
}

void	print_hexadecimal(t_format *t, size_t n)
{
	size_t	final_len;
	size_t	prec_len;

	if (t->has_precision)
		t->flags[1] = 0;
	final_len = hex_width(t, n);
	prec_len = t->precision - final_len;
	handle_init(n, t, &final_len, &prec_len);
	if (t->precision == 0 && t->has_precision && n == 0)
	{
		if (t->width > 0)
			print_blanks((t->width), t);
		return ;
	}
	if ((t->width) > final_len)
	{
		if (t->flags[0])
			handle_width_one(t, n, final_len, prec_len);
		else
			handle_width_two(t, n, final_len, prec_len);
	}
	else
		handle_no_width(t, n, prec_len);
}
