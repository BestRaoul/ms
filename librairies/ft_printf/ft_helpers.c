/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:28:28 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/15 11:32:07 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*last(char *s)
{
	return (&s[ft_strlen(s)]);
}

int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}
