/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:24:24 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/31 16:24:26 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	str_contains_flag(char *str, t_format *t)
{
	return (cab_(str, '-') || (cab_(str, '0') && !t->flags[1])
		|| cab_(str, '#') || cab_(str, ' ') || cab_(str, '+'));
}

void	set_flag(t_format *t, char c)
{
	if (c == '-')
		t->flags[0] = 1;
	if (c == '0')
		t->flags[1] = 1;
	if (c == '#')
		t->flags[2] = 1;
	if (c == ' ')
		t->flags[3] = 1;
	if (c == '+')
		t->flags[4] = 1;
	if (t->flags[0])
		t->flags[1] = 0;
	if (t->flags[4])
		t->flags[3] = 0;
}

void	get_flags(t_format *t, char **str)
{
	while (**str)
	{
		if (!str_contains_flag(*str, t))
			return ;
		else
			set_flag(t, **str);
		(*str)++;
	}
}
