/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:03:53 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 14:03:56 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (0);
	ft_strlcpy(res, s, ft_strlen(s) + 1);
	return (res);
}
