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
		ft_printf("[[%d] `%s`]", ((t_dict_int_str_member *)
				ft_lst_get(lst, i)->content)->key, ((t_dict_int_str_member *)
				ft_lst_get(lst, i)->content)->value);
		ft_printf(" ");
		i ++;
	}
	ft_printf("\n");
}

static int	print_type2(int type)
{
	int	t;

	if (type == LITERAL)
		ft_printf("literal");
	if (type == LITERAL_SQ)
		ft_printf("literal sq");
	if (type == LITERAL_NQ)
		ft_printf("literal nq");
	if (type == LITERAL_DQ)
		ft_printf("literal dq");
	if (type == PIPELINE)
		ft_printf("pipeline");
	if (type == PIPELINELIST)
		ft_printf("pipeline lst");
	if (type == HEREDOC)
		ft_printf("heredoc");
	t = type;
	return (t == LITERAL || t == LITERAL_SQ || t == LITERAL_NQ
		|| t == LITERAL_DQ
		|| t == PIPELINE || t == PIPELINELIST || t == HEREDOC);
}

void	print_type(int type)
{
	ft_printf("%s", RED);
	if (type == LPAREN)
		ft_printf("(");
	else if (type == RPAREN)
		ft_printf(")");
	else if (type == PIPE)
		ft_printf("|");
	else if (type == REDIRLEFT)
		ft_printf("<");
	else if (type == REDIRRIGHT)
		ft_printf(">");
	else if (type == HEREDOCOP)
		ft_printf("<<");
	else if (type == APPEND)
		ft_printf(">>");
	else if (type == AND)
		ft_printf("&&");
	else if (type == OR)
		ft_printf("||");
	else if (!print_type2(type))
		ft_printf("BIG ERROR");
	ft_printf("%s", RESET);
}

void	print_lex2(t_list *lst)
{
	int	i;
	int	k;

	i = 0;
	ft_printf("lexemes:\n");
	while (i < ft_lstsize(lst))
	{
		ft_printf(" [");
		k = ((t_dict_int_str_member *) ft_lst_get(lst, i)->content)->key;
		print_type(k);
		if (k == 10 || k == 11 || k == 12)
			ft_printf(": `%s`", ((t_dict_int_str_member *)
					ft_lst_get(lst, i)->content)->value);
		ft_printf("]\n");
		i ++;
	}
	ft_printf("\n");
}
