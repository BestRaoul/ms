/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadecimal_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 19:09:33 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/13 19:09:34 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	handle_no_width(t_format *t, size_t n, size_t prec_len)
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
}
