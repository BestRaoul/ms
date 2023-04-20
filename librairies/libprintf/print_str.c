/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:38:31 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/03 14:38:32 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	print_str(t_format *t, char *str)
{
	size_t	precision;
	size_t	final_str_len;

	precision = t->precision;
	if (!str)
		str = "(null)";
	if (!t->has_precision)
		precision = ft_strlen_(str);
	final_str_len = ft_min_(precision, ft_strlen_(str));
	if ((t->width) > final_str_len)
	{
		if (t->flags[0])
		{
			put_str_len(str, final_str_len, t);
			print_blanks(t->width - final_str_len, t);
		}
		else
		{
			print_blanks(t->width - final_str_len, t);
			put_str_len(str, final_str_len, t);
		}
	}
	else
		put_str_len(str, final_str_len, t);
}
