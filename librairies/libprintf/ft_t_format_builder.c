/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_format_builder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:14:03 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/31 15:14:04 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

t_format	*build_format(char **str)
{
	t_format	*res;

	res = ft_calloc_(1, sizeof(*res));
	if (!res)
		return (0);
	(*str)++;
	get_flags(res, str);
	if (!get_width(res, str))
		return (0);
	if (!get_precision(res, str))
		return (0);
	get_conversion(res, str);
	res->chars_printed = 0;
	return (res);
}
