/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:24:49 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/03 16:24:51 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static size_t	my_pow(size_t a, size_t b)
{
	size_t	res;
	size_t	i;

	res = 1;
	i = 0;
	while (i < b)
	{
		res *= a;
		i ++;
	}
	return (res);
}

void	ft_put_size_t(size_t n, t_format *t)
{
	size_t	i;
	size_t	temp;

	i = 0;
	while (i < unsigned_num_width_size_t(n, 10))
	{
		temp = (n / my_pow(10, unsigned_num_width_size_t(n, 10) - i - 1)) % 10;
		count_put_char(temp + '0', t);
		i ++;
	}
}
