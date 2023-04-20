/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:50:08 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 14:50:11 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

/*static unsigned int	my_max(unsigned int a, unsigned int b)
{
	if (a == UINT_MAX)
		return (a);
	if (b == UINT_MAX)
		return (b);
	if (a > b)
		return (a);
	return (b);
}*/

static unsigned int	my_min(unsigned int a, unsigned int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	final_len;

	if (start >= ft_strlen(s))
	{
		res = malloc(1);
		if (!res)
			return (0);
		res[0] = 0;
		return (res);
	}
	final_len = my_min(len, ft_strlen(s) - start) + 1;
	res = malloc(final_len);
	if (!res)
		return (0);
	s += start;
	ft_strlcpy(res, s, final_len);
	return (res);
}
