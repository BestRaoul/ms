/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:28:28 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/15 11:32:07 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_append_num(char *str, long x, int width, char *base)
{
	int	i;
	int	div;

	div = ft_strlen(base);
	if (x < 0)
		x = -x;
	i = 0;
	while (i < width)
	{
		str[width - i - 1] = base[x % div];
		x /= div;
		i++;
	}
	str[i] = 0;
}

void	ft_append_ul(char *str, unsigned long x, int width, char *base)
{
	int	i;
	int	div;

	div = ft_strlen(base);
	i = 0;
	while (i < width)
	{
		str[width - i - 1] = base[x % div];
		x /= div;
		i++;
	}
	str[i] = 0;
}

int	long_size(long x, int div)
{
	int	c;

	if (x == 0)
		return (1);
	if (x < 0)
		x = -x;
	c = 0;
	while (x > 0)
	{
		x /= div;
		c++;
	}
	return (c);
}

int	ulong_size(unsigned long x, int div)
{
	int	c;

	if (x == 0)
		return (1);
	c = 0;
	while (x > 0)
	{
		x /= div;
		c++;
	}
	return (c);
}
