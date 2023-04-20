/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:53:10 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/31 16:53:11 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	has_width(const char *str)
{
	return (ft_isdigit_(*str) || *str == '*');
}

size_t	get_width_chr_width(const char *str)
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

int	get_width_2(t_format *t, char **str)
{
	char	*temp;
	size_t	i;

	temp = malloc(get_width_chr_width(*str) + 1);
	if (!temp)
		return (0);
	i = -1;
	while (++i < get_width_chr_width(*str))
		temp[i] = (*str)[i];
	temp[i] = 0;
	t->width = ft_atoi_(temp);
	free(temp);
	*str += get_width_chr_width(*str);
	return (1);
}

int	get_width(t_format *t, char **str)
{
	if (has_width(*str))
	{
		if (**str == '*')
		{
			t->width = 0;
			(*str)++;
		}
		else
		{
			if (!get_width_2(t, str))
				return (0);
		}
	}
	else
		t->width = 0;
	return (1);
}
