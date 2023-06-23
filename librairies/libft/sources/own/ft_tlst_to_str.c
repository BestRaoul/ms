/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tlst_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_arr(t_list *lst)
{
	t_list	*iter;
	size_t	i;
	char	*res;

	res = gc_malloc(sizeof(*res) * (ft_lstsize(lst) + 1));
	if (!res)
		return (NULL);
	iter = lst;
	i = 0;
	while (iter)
	{
		res[i] = ((char *)(iter->content))[0];
		iter = iter->next;
		i ++;
	}
	res[i] = '\0';
	return (res);
}

/* Combines lst of null terminated SINGLE CHARS into a string */
char	*ft_tlst_to_str(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (ft_lstsize(lst) == 0)
		return (NULL);
	return (create_arr(lst));
}
