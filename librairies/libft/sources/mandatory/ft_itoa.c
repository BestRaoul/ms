/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:11 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/25 14:31:13 by jwikiera         ###   ########.fr       */
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

static int	handle_neg(int *n, int *i, char **res)
{
	if (*n >= 0)
	{
		*i = 0;
		*res = malloc(res_len(*n) + 1);
		return (0);
	}
	*i = 1;
	*res = malloc(res_len(*n) + 2);
	if (*res)
		(*res)[0] = '-';
	return (1);
}

static int	my_abs_(int a)
{
	if (a < 0)
		return (a * -1);
	return (a);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		neg;

	neg = handle_neg(&n, &i, &res);
	if (!res)
		return (0);
	while (i - neg < res_len(n))
	{
		res[i] = my_abs_((n / my_pow(10,
						res_len(n) - (i - neg) - 1)) % 10) + '0';
		i ++;
	}
	res[i] = 0;
	return (res);
}
