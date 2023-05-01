/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexeme_tlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	print_lexeme_tlist(t_list *lst)
{
	int	i;

	i = 0;
	ft_printf("lexemes:\n");
	while (i < ft_lstsize(lst))
	{
		ft_printf("[[%d] `%s`]", ((t_dict_int_str_member *) ft_lst_get(lst, i)->content)->key, ((t_dict_int_str_member *) ft_lst_get(lst, i)->content)->value);
		ft_printf(" ");
		i ++;
	}
	ft_printf("\n");
}
