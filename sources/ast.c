/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"



t_ast_node	*init_ast_node(int isleaf, t_dict_int_str_member lexeme, int branchnum)
{
	t_ast_node	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->content = malloc(sizeof(*res->content) * (ft_strlen(lexeme.value) + 1));
	if (!res->content)
	{
		free (res);
		return (NULL);
	}
	ft_memcpy(res->content, lexeme.value, ft_strlen(lexeme.value) + 1);
	res->is_leaf = isleaf;
	res->type = lexeme.key;
	res->branches = malloc(sizeof(*res->branches) * branchnum);
	if (!res->branches)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

/*int	get_next_rule() {

}*/

/* This gets the current i type (should be a terminal or nonterminal enum) */
int	peek_type(int i, t_list *lst)
{
	t_list	*current;

	if (i >= ft_lstsize(lst))
		return (-1);
	current = ft_lst_get(lst, i);
	if (!current)
		return (-1);
	return (((t_dict_int_str_member *)current->content)->key);
}

int	get_in_grammar(int type, int min_index)
{
	int		i;

	i = 0;
	while (i < grammar.num_rules)
	{
		if (grammar.rules[i].name == type && i > min_index)
			return (i);
		i ++;
	}
	return (-1);
}

int	get_terminal(int type)
{
	int	grammar_index = get_in_grammar(type, -1);
	if (grammar_index == -1)
		return (-1);

}

int	is_pipeline(int i, t_list *lexemes)
{

}


t_ast_node	*lexemes_to_ast(t_list *lexemes, t_ast_node *res, int lex_pointer, int gram_pointers[2])
{
	//t_ast_node	*res;

	if (res == NULL)
	{
		res = malloc(sizeof(*res));
		if (!res)
			return (NULL);
		res->is_leaf = 0;
		res->type = CMDLINE;
		lex_pointer = 0;
	}
	//gram_pointers are the depth and left to right pointers in the grammar struct
	// this func needs to call itself for every nonterminal in the RHS of the current grammar rule
	// one question, how to get back if something doesn't match, in the recursion
	return (res);
}
