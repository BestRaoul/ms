/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_void_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:19:50 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/03 16:19:51 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

size_t	ptr_width(void *ptr)
{
	return (unsigned_num_width_size_t((size_t) ptr, 16) + 2);
}

void	print_void_ptr(t_format *t, void *ptr)
{
	t->chars_printed += (int)ptr_width(ptr);
	if ((t->width) > ptr_width(ptr))
	{
		if (t->flags[0])
		{
			put_hex_fd((size_t)ptr, 0, 1, 1);
			print_blanks(t->width - ptr_width(ptr), t);
		}
		else
		{
			print_blanks(t->width - ptr_width(ptr), t);
			put_hex_fd((size_t)ptr, 0, 1, 1);
		}
	}
	else
		put_hex_fd((size_t)ptr, 0, 1, 1);
}
