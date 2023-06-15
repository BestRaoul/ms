/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tlst_to_strarr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**create_arr(t_list *lst)
{
	t_list	*iter;
	size_t	i;
	char	**res;

	res = MALLOC(sizeof(*res) * (ft_lstsize(lst) + 1));
	if (!res)
		return (NULL);
	iter = lst;
	i = 0;
	while (iter)
	{
		res[i] = MALLOC(sizeof(**res) * (ft_strlen(iter->content) + 1));
		if (!res[i])
		{
			ft_free_split(res, i);
			return (NULL);
		}
		ft_strlcpy(res[i], iter->content, ft_strlen(iter->content) + 1);
		iter = iter->next;
		i ++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_tlst_to_strarr(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (ft_lstsize(lst) == 0)
		return (NULL);
	return (create_arr(lst));
}
