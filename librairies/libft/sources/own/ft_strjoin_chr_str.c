/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_chr_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:44:57 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/21 11:45:03 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_chr_str(char c, const char *str)
{
	char	*tmp;
	char	*join;

	tmp = MALLOC(sizeof(*tmp) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = c;
	tmp[1] = 0;
	join = ft_strjoin(tmp, str);
	free(tmp);
	return (join);
}
