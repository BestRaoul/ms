/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:48:16 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/17 16:01:45 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

//"diuoxXfFeEgGaAcspn%"
int	ft_is_specifier(char c)
{
	return (ft_find(c, "diuxXcsp%") != -1);
}

int	ft_is_flag(char c)
{
	if (c == '-')
		return (0);
	else if (c == '+')
		return (1);
	else if (c == ' ')
		return (2);
	else if (c == '#')
		return (3);
	else if (c == '0')
		return (4);
	return (-1);
}
