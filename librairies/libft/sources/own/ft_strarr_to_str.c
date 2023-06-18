/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:20:59 by pkondrac          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:27 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strarr_to_str(char **strarr, char sep)
{
	size_t	i;
	t_list	*lst;
	char	*res;

	lst = NULL;
	i = 0;
	while (i < ft_strarrlen(strarr))
	{
		if (!ft_lstadd_str(strarr[i], &lst))
		{
			ft_lstclear(&lst, ft_delnode);
			return (NULL);
		}
		i ++;
	}
	res = ft_str_tlst_to_str_join(lst, sep);
	ft_lstclear(&lst, ft_delnode);
	return (res);
}