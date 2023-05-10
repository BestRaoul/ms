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

//--IGNORE NORME
static void	print_type(int type)
{
	ft_printf("%s", RED);
	if (type < 10) ft_printf("%s", BRED);
	switch(type)
	{
		case 0: ft_printf("("); break;
		case 1: ft_printf(")"); break;
		case 2: ft_printf("|"); break;
		case 3: ft_printf("<"); break;
		case 4: ft_printf(">"); break;
		case 5: ft_printf("="); break;
		case 6: ft_printf("<<"); break;
		case 7: ft_printf(">>"); break;
		case 8: ft_printf("&&"); break;
		case 9: ft_printf("||"); break;
		case 10: ft_printf("literal"); break;
		case 11: ft_printf("literal sq"); break;
		case 12: ft_printf("literal dq"); break;
		default: ft_printf("BIG ERROR"); break;
	}
	ft_printf("%s", RESET);
}

void	print_lexeme_tlist2(t_list *lst)
{
	int	i;

	i = 0;
	ft_printf("lexemes:\n");
	while (i < ft_lstsize(lst))
	{
		ft_printf(" [");
		int k = ((t_dict_int_str_member *) ft_lst_get(lst, i)->content)->key;
		print_type(k);
		if (k == 10 || k == 11 || k == 12)
			ft_printf(": `%s`", ((t_dict_int_str_member *) ft_lst_get(lst, i)->content)->value);
		ft_printf("]\n");
		i ++;
	}
	ft_printf("\n");
}
