/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:32:53 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/04 17:32:54 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

size_t	unsigned_num_width_size_t(size_t n, int base)
{
	size_t	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n /= base;
		i ++;
	}
	return (i);
}

size_t	signed_width_size_t(int n, int base)
{
	int	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n /= base;
		i ++;
	}
	if (n < 0)
		i ++;
	return (i);
}

int	int_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	count_put_char(char c, t_format *t)
{
	ft_putchar_fd_(c, 1);
	t->chars_printed ++;
}

void	count_put_str(char *str, t_format *t)
{
	t->chars_printed += (int)ft_strlen_(str);
	ft_putstr_fd_(str, 1);
}
