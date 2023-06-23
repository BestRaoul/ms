/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powertrim_chr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:56:19 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/21 11:56:20 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Trims all spaces and the provided char. */
char	*ft_powertrim_chr(const char *str, char c)
{
	char	*joined_set;
	char	*res;

	joined_set = gc_malloc(sizeof(" \f\n\r\t\v") + 2);
	if (!joined_set)
		return (NULL);
	joined_set[0] = c;
	if (!ft_strlcpy(joined_set + 1, " \f\n\r\t\v",
			ft_strlen(" \f\n\r\t\v") + 1))
		return (0);
	res = ft_strtrim(str, joined_set);
	gc_free(joined_set);
	return (res);
}
