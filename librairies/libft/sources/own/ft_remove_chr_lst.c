/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_chr_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lst_has_c(t_list *lst, char c)
{
	int	i;

	i = 0;
	while (i < ft_lstsize(lst))
	{
		if (((char *)ft_lst_get(lst, i)->content)[0] == c)
			return (1);
		i ++;
	}
	return (0);
}

/* removes all occurences of c in a t_list */
void	ft_remove_chr_lst(t_list **lst, char c)
{
	int		i;

	while (lst_has_c(*lst, c))
	{
		i = 0;
		while (i < ft_lstsize(*lst))
		{
			if (((char *)ft_lst_get(*lst, i)->content)[0] == c)
			{
				ft_lst_rm(lst, i);
				break ;
			}
			i ++;
		}
	}
}
