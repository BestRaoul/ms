/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:11:44 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 18:11:45 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	clrlst(t_list *lst, void *res, void (*del)(void *))
{
	if (!res)
	{
		ft_lstclear(&lst, del);
		return (1);
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;
	void	*cont;

	new_lst = 0;
	while (lst)
	{
		cont = f(lst->content);
		if (clrlst(new_lst, cont, del))
			return (0);
		temp = ft_lstnew(cont);
		if (clrlst(new_lst, temp, del))
		{
			free(cont);
			return (0);
		}
		if (!new_lst)
			new_lst = temp;
		else
			ft_lstadd_back(&new_lst, temp);
		lst = lst->next;
	}
	return (new_lst);
}
