/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:08:18 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/27 16:08:19 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	res_len(int n)
{
	int	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n /= 10;
		i ++;
	}
	return (i);
}

static int	my_pow(int a, int b)
{
	int	res;
	int	i;

	res = 1;
	i = 0;
	while (i < b)
	{
		res *= a;
		i ++;
	}
	return (res);
}

static int	handle_neg(int *n, int *i, int fd)
{
	if (*n >= 0)
	{
		*i = 0;
		return (0);
	}
	*i = 1;
	write (fd, "-", 1);
	return (1);
}

static int	my_abs(int a)
{
	if (a < 0)
		return (a * -1);
	return (a);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	neg;
	int	i;
	int	temp;

	neg = handle_neg(&n, &i, fd);
	while (i - neg < res_len(n))
	{
		temp = (n / my_pow(10, res_len(n) - (i - neg) - 1)) % 10;
		ft_putchar_fd(my_abs(temp) + '0', fd);
		i ++;
	}
}
