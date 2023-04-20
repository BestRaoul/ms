/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:31:11 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/07 16:31:12 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static void	part_one(t_format *t, size_t n, size_t final_len, size_t prec_len)
{
	if (t->flags[0])
	{
		if (t->precision > unsigned_num_width_size_t(n, 10))
			print_zeroes(prec_len, t);
		ft_put_size_t(n, t);
		print_blanks((t->width) - final_len, t);
	}
	else
	{
		if (!t->flags[1])
			print_blanks((t->width) - final_len, t);
		if (t->flags[1])
			print_zeroes((t->width) - final_len, t);
		if (t->precision > unsigned_num_width_size_t(n, 10))
			print_zeroes(prec_len, t);
		ft_put_size_t(n, t);
	}
}

static void	part_two(t_format *t, size_t n, size_t prec_len)
{
	if (t->precision > unsigned_num_width_size_t(n, 10))
		print_zeroes(prec_len, t);
	ft_put_size_t(n, t);
}

void	print_unsigned(t_format *t, size_t n)
{
	size_t	final_len;
	size_t	prec_len;

	if (t->has_precision)
		t->flags[1] = 0;
	final_len = unsigned_num_width_size_t(n, 10);
	prec_len = t->precision - final_len;
	if (t->precision > final_len)
		final_len += prec_len;
	if (t->flags[3] || t->flags[4])
		final_len ++;
	if (t->precision == 0 && t->has_precision && n == 0)
	{
		if (t->width > 0)
			print_blanks((t->width), t);
		return ;
	}
	if ((t->width) > final_len)
		part_one(t, n, final_len, prec_len);
	else
		part_two(t, n, prec_len);
}
