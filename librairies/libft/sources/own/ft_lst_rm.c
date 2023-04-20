/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del_middle(t_list **lst, int index)
{
	int		i;
	t_list	**iter;
	t_list	*bak;

	iter = lst;
	i = 0;
	while (i < index - 1)
	{
		iter = &(*iter)->next;
		i ++;
	}
	bak = (*iter)->next->next;
	ft_lstdelone((*iter)->next, ft_delnode);
	(*iter)->next = bak;
}

/* Deletes a t_list node seamlessly (no gaps in resulting t_list) */
void	ft_lst_rm(t_list **lst, int index)
{
	t_list	*bak;

	if (ft_lstsize(*lst) == 0)
		return ;
	if (index < 0)
		index = ft_lstsize(*lst) + index;
	if (index < 0)
		return ;
	if (ft_lstsize(*lst) == 1 || index == ft_lstsize(*lst) - 1)
	{
		ft_lstdelone(*lst, ft_delnode);
		return ;
	}
	if (index == 0)
	{
		bak = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(bak, ft_delnode);
		return ;
	}
	del_middle(lst, index);
}
