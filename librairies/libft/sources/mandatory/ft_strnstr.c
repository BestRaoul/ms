/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:45:57 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/19 16:45:58 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (ft_strlen(needle) > ft_strlen(haystack))
		return (0);
	if (!ft_strlen(needle))
		return ((char *) haystack);
	i = 0;
	while (i < len && *haystack)
	{
		if (len - i < ft_strlen(needle))
			return (0);
		if (!ft_strncmp(&haystack[i], needle, ft_strlen(needle)))
			return ((char *) &haystack[i]);
		i ++;
	}
	return (0);
}
