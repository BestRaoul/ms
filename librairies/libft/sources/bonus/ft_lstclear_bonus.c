/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:26:57 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/03 14:55:04 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*last;
	t_list	*last2;

	if (!lst)
		return ;
	last = *lst;
	while (last)
	{
		last2 = last->next;
		ft_lstdelone(last, del);
		last = last2;
	}
	*lst = 0;
}
