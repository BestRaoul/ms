/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	has_num_digits(const char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i])
			&& str[i] != '-' && str[i] != '+')
			return (0);
		i ++;
	}
	return (1);
}

static char	*inttrim(const char *str)
{
	char	*trimmed;
	char	*res;
	int		i;

	trimmed = ft_powertrim(str, "+-");
	if (ft_strlen(trimmed) == 1 && trimmed[0] == '0')
		return (trimmed);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (trimmed[i] && trimmed[i] == '0')
		i ++;
	res = MALLOC(ft_strlen(trimmed) - i + 1);
	if (!res)
	{
		FREE(trimmed);
		return (NULL);
	}
	ft_strlcpy(res, trimmed + i, ft_strlen(trimmed) - i + 1);
	FREE(trimmed);
	return (res);
}

static int	has_only_digits(const char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

static int	free_trimmed(char *str)
{
	if (str)
		FREE(str);
	return (0);
}

int	ft_str_is_int(const char *str)
{
	char	*trimmed;
	int		sign;

	if (!str || !has_num_digits(str))
		return (0);
	sign = ft_get_str_sign(str);
	trimmed = inttrim(str);
	if (!trimmed || ft_strlen(trimmed) == 0)
		return (free_trimmed(trimmed));
	if (!has_only_digits(trimmed))
		return (free_trimmed(trimmed));
	if (ft_strlen(trimmed) > 10)
		return (free_trimmed(trimmed));
	if (ft_atoi_l(trimmed) * sign > INT_MAX
		|| ft_atoi_l(trimmed) * sign < INT_MIN)
		return (free_trimmed(trimmed));
	FREE(trimmed);
	return (1);
}
