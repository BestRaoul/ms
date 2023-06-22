/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

/* 
 * Returns allocated string of first consecutive matching characters
 * also moves the pointer along the scan
 */
char	*_scan2(char **str_ptr, int (*checker)(char c))
{
	char	*res;
	int		i;

	i = findf_nt(checker, *str_ptr);
	res = chop(*str_ptr, i - 1);
	*str_ptr += i;
	return (res);
}

int	strarr_count(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
		i++;
	return (i);
}

char	**realloc_strarr_no_gc(char **strarr)
{
	char	**res;
	int		i;

	res = ft_calloc((strarr_count(strarr) + 1), sizeof(char *));
	garbage_collector(REMOVE, res);
	i = 0;
	while (strarr[i])
	{
		res[i] = ft_strdup(strarr[i]);
		garbage_collector(REMOVE, res[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	next(t_list **i_ptr)
{
	*i_ptr = (*i_ptr)->next;
}
