/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powertrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:56:19 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/21 11:56:20 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_powertrim(const char *str, const char *set)
{
	char	*joined_set;
	char	*res;

	joined_set = ft_strjoin(set, " \f\n\r\t\v");
	if (!joined_set)
		return (NULL);
	res = ft_strtrim(str, joined_set);
	free(joined_set);
	return (res);
}
