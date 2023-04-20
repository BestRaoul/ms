/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:37:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/04 18:37:58 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static int	part_one(t_format *t, int n)
{
	if (t->precision == 0 && t->has_precision && n == 0)
	{
		if ((t->flags[4] || t->flags[3]) && t->flags[0])
		{
			if (t->flags[4])
				count_put_char('+', t);
			else if (t->width == 0)
				count_put_char(' ', t);
		}
		if (t->width > 0)
			print_blanks(t->width - 1 * t->flags[4], t);
		if ((t->flags[4] || t->flags[3]) && !t->flags[0])
		{
			if (t->flags[4])
				count_put_char('+', t);
			else if (t->width == 0)
				count_put_char(' ', t);
		}
		return (1);
	}
	return (0);
}

static void	part_two(t_format *t, int n, size_t final_len, size_t prec_len)
{
	if (t->flags[3] && n >= 0)
		count_put_char(' ', t);
	if (t->flags[4] && n >= 0)
		count_put_char('+', t);
	if (n < 0)
		count_put_char('-', t);
	if (t->precision > unsigned_num_width_size_t(my_abs_(n), 10))
		print_zeroes(prec_len, t);
	t->chars_printed += (int)signed_width_size_t(my_abs_(n), 10);
	if (n == INT_MIN)
	{
		ft_putnbr_fd_(my_abs_(n / 10), 1);
		ft_putchar_fd_('8', 1);
	}
	else
		ft_putnbr_fd_(my_abs_(n), 1);
	print_blanks((t->width) - final_len, t);
}

static void	part_three(t_format *t, int n, size_t final_len, size_t prec_len)
{
	if (!t->flags[1])
		print_blanks((t->width) - final_len, t);
	if (t->flags[3] && n >= 0)
		count_put_char(' ', t);
	if (t->flags[4] && n >= 0)
		count_put_char('+', t);
	if (n < 0)
		count_put_char('-', t);
	if (t->flags[1])
		print_zeroes((t->width) - final_len, t);
	if (t->precision > unsigned_num_width_size_t(my_abs_(n), 10))
		print_zeroes(prec_len, t);
	t->chars_printed += (int)signed_width_size_t(my_abs_(n), 10);
	if (n == INT_MIN)
	{
		ft_putnbr_fd_(my_abs_(n / 10), 1);
		ft_putchar_fd_('8', 1);
	}
	else
		ft_putnbr_fd_(my_abs_(n), 1);
}

static void	part_four(t_format *t, int n, size_t prec_len)
{
	if (t->flags[3] && n >= 0)
		count_put_char(' ', t);
	if (t->flags[4] && n >= 0)
		count_put_char('+', t);
	if (n < 0)
		count_put_char('-', t);
	if (t->precision > unsigned_num_width_size_t(my_abs_(n), 10))
		print_zeroes(prec_len, t);
	t->chars_printed += (int)signed_width_size_t(my_abs_(n), 10);
	if (n == INT_MIN)
	{
		ft_putnbr_fd_(my_abs_(n / 10), 1);
		ft_putchar_fd_('8', 1);
	}
	else
		ft_putnbr_fd_(my_abs_(n), 1);
}

void	print_int(t_format *t, int n)
{
	size_t	final_len;
	size_t	prec_len;

	if (t->has_precision)
		t->flags[1] = 0;
	final_len = unsigned_num_width_size_t(my_abs_(n), 10);
	prec_len = t->precision - final_len;
	if (t->precision > final_len)
		final_len += prec_len;
	if (n >= 0 && (t->flags[3] || t->flags[4]))
		final_len ++;
	if (n < 0)
		final_len ++;
	if (part_one(t, n))
		return ;
	if ((t->width) > final_len)
	{
		if (t->flags[0])
			part_two(t, n, final_len, prec_len);
		else
			part_three(t, n, final_len, prec_len);
	}
	else
		part_four(t, n, prec_len);
}
