/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:14:17 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/01 15:14:24 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	print_percent(t_format *t)
{
	char	c;

	c = '%';
	if (t->width > 0)
	{
		if (t->flags[0])
		{
			count_put_char(c, t);
			if (t->flags[1])
				print_zeroes(t->width - 1, t);
			else
				print_blanks(t->width - 1, t);
		}
		else
		{
			if (t->flags[1])
				print_zeroes(t->width - 1, t);
			else
				print_blanks(t->width - 1, t);
			count_put_char(c, t);
		}
	}
	else
		count_put_char(c, t);
}
