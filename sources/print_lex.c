/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	print_lex(t_list *lst)
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

void	print_type(int type)
{
	ft_printf("%s", RED);
	switch(type)
	{
		case LPAREN: ft_printf("("); break;
		case RPAREN: ft_printf(")"); break;
		case PIPE: ft_printf("|"); break;
		case REDIRLEFT: ft_printf("<"); break;
		case REDIRRIGHT: ft_printf(">"); break;
		case HEREDOCOP: ft_printf("<<"); break;
		case APPEND: ft_printf(">>"); break;
		case AND: ft_printf("&&"); break;
		case OR: ft_printf("||"); break;
		case LITERAL: ft_printf("literal"); break;
		case LITERAL_NQ: ft_printf("literal nq"); break;
		case LITERAL_SQ: ft_printf("literal sq"); break;
		case LITERAL_DQ: ft_printf("literal dq"); break;
		case PIPELINE: ft_printf("pipeline"); break;
		case PIPELINELIST: ft_printf("pipeline_lst"); break;
		case HEREDOC: ft_printf("heredoc"); break;
		default: ft_printf("BIG ERROR"); break;
	}
	ft_printf("%s", RESET);
}

void	print_lex2(t_list *lst)
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
