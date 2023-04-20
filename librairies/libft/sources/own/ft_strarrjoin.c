/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_arr(t_list **lst, char **arr)
{
	char	*tempdup;
	size_t	i;

	i = 0;
	while (i < ft_strarrlen(arr))
	{
		tempdup = ft_strdup(arr[i]);
		if (!tempdup)
		{
			ft_lstclear(lst, ft_delnode);
			return (0);
		}
		if (!ft_lstadd_str(tempdup, lst))
		{
			free(tempdup);
			ft_lstclear(lst, ft_delnode);
			return (0);
		}
		i ++;
	}
	return (1);
}

/* joins two NULL terminated string arrays */
char	**ft_strarrjoin(char **arr1, char **arr2)
{
	t_list	*lst;
	char	**res;

	if (!arr1 || !arr2)
		return (NULL);
	lst = NULL;
	if (!add_arr(&lst, arr1))
		return (NULL);
	if (!add_arr(&lst, arr2))
		return (NULL);
	res = ft_tlst_to_strarr(lst);
	ft_lstclear(&lst, ft_delnode);
	return (res);
}
