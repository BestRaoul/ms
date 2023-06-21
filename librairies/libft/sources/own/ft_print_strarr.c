/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strarr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_empty(void)
{
	if (!ft_ptstrfd_s("NULL PTR", 1))
		return (0);
	return (1);
}

static size_t	len_from_null_terminated(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len ++;
	return (len);
}

int	ft_print_strarr(char **arr, size_t len, int null_terminated)
{
	size_t	i;

	if (!arr)
		return (print_empty());
	if (null_terminated)
		len = len_from_null_terminated(arr);
	if (!ft_ptstrfd_s("[", 1))
		return (0);
	i = 0;
	while (i < len)
	{
		if (!ft_ptstrfd_s(arr[i], 1))
			return (0);
		if (i < len - 1)
		{
			if (!ft_ptstrfd_s("|", 1))
				return (0);
		}
		i ++;
	}
	if (!ft_ptstrfd_s("]", 1))
		return (0);
	return (1);
}
