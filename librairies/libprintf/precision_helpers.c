/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 09:52:58 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/01 09:52:59 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	has_precision(const char *str)
{
	return (*str == '.');
}

size_t	get_precision_chr_width(const char *str)
{
	size_t	res;

	res = 0;
	while (ft_isdigit_(*(str + res)))
	{
		if (!ft_isdigit_(*(str + res)))
			return (res - 1);
		res++;
	}
	return (res);
}

int	get_precision2(t_format *t, char **str)
{
	char	*temp;
	size_t	i;

	(*str)++;
	temp = malloc(get_precision_chr_width(*str) + 1);
	if (!temp)
		return (0);
	i = -1;
	while (++i < get_precision_chr_width(*str))
		temp[i] = (*str)[i];
	temp[i] = 0;
	t->precision = ft_atoi_(temp);
	free(temp);
	*str += get_precision_chr_width(*str);
	return (1);
}

int	get_precision(t_format *t, char **str)
{
	t->has_precision = 1;
	if (has_precision(*str))
	{
		if (!ft_isdigit_(*((*str) + 1)))
		{
			t->precision = 0;
			(*str)++;
		}
		else
		{
			if (!get_precision2(t, str))
				return (0);
		}
	}
	else
	{
		t->precision = 0;
		t->has_precision = 0;
	}
	return (1);
}
