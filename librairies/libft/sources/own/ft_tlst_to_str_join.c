/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tlst_to_str_join.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_arr(t_list *lst, char sep)
{
	t_list	*iter;
	int		i;
	char	*res;

	res = MALLOC(sizeof(*res) * (ft_lstsize(lst) + 1
				+ ft_max_int(ft_lstsize(lst) - 1, 0)));
	if (!res)
		return (NULL);
	iter = lst;
	i = 0;
	while (iter)
	{
		res[i] = ((char *)(iter->content))[0];
		if (i < ft_lstsize(lst) - 1)
		{
			res[i + 1] = sep;
			i += 2;
		}
		else
			i ++;
		iter = iter->next;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_tlst_to_str_join(t_list *lst, char sep)
{
	if (!lst)
		return (NULL);
	if (ft_lstsize(lst) == 0)
		return (NULL);
	return (create_arr(lst, sep));
}
