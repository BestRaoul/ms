/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:28:25 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:28:26 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* gets t_list at index, supports negative indexes */
t_list	*ft_lst_get(t_list *lst, ssize_t index)
{
	ssize_t	i;

	if (!lst)
		return (NULL);
	if (index < 0)
		index = ft_lstsize(lst) + index;
	if (index < 0)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (i == index)
			return (lst);
		lst = lst->next;
		i ++;
	}
	return (NULL);
}
