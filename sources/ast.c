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

/* This gets the next i type (should be a terminal or nonterminal enum) */
int	peek_type(int i, t_list *lst)
{
	t_list	*current;

	if (i >= ft_lstsize(lst) - 1)
		return (END);
	current = ft_lst_get(lst, i + 1);
	if (!current)
		return (FAILED);
	return (((t_dict_int_str_member *)current->content)->key);
}

int	current_type(int i, t_list *lst)
{
	t_list	*current;

	if (i > ft_lstsize(lst) - 1)
		return (FAILED);
	current = ft_lst_get(lst, i);
	if (!current)
		return (FAILED);
	return (((t_dict_int_str_member *)current->content)->key);
}

int	prs_arg(int i, t_list *lexemes)
{
	int		current;

	current = current_type(i, lexemes);
	if (current == LITERAL_NQ || current == LITERAL_SQ || current == LITERAL_DQ)
	{
		ft_printf("(CmdArg %s)", ((t_dict_int_str_member *) ft_lst_get(lexemes, i)->content)->value);
		return (1);
	}
	printf("Error, expected command or command argument");
	return (-1);
}

int	prs_heredoc(int i, t_list *lexemes)
{
	if (peek_type(i, lexemes) != LITERAL_NQ || peek_type(i, lexemes) != LITERAL_NQ || peek_type(i, lexemes) != LITERAL_NQ)
	{
		ft_printf("Heredoc delimiter expected!");
		return (-1);
	}
	ft_printf("(Heredoc %s)", ((t_dict_int_str_member *) ft_lst_get(lexemes, i + 1)->content)->value);
	return (2);
}

int	prs_redir(int i, t_list *lexemes)
{
	int		peek;
	int		current;
	char	*redir_str;
	int		argres;

	current = current_type(i, lexemes);
	redir_str = ">>";
	if (current == REDIRLEFT)
		redir_str = "<";
	if (current == REDIRRIGHT)
		redir_str = ">";
	peek = peek_type(i, lexemes);
	if (peek == LITERAL_NQ || peek == LITERAL_SQ || peek == LITERAL_DQ)
	{
		ft_printf("(Redir %s ", redir_str);
		argres = prs_arg(i + 1, lexemes);
		if (argres == -1)
			return (-1);
		ft_printf(")");
		return (1 + argres);
	}
	else
	{
		ft_printf("Command or filename expected! ");
		return (-1);
	}
}

int	prs_suffix(int i, t_list *lexemes)
{
	int	current;
	int	pipeline_res;

	current = current_type(i, lexemes);
	if (current == PIPE)
	{
		ft_printf("(Suffix | ");
		pipeline_res = prs_pipeline(i + 1, lexemes);
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else if (current == AND)
	{
		ft_printf("(Suffix && ");
		pipeline_res = prs_pipeline(i + 1, lexemes);
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else if (current == OR)
	{
		ft_printf("(Suffix || ");
		pipeline_res = prs_pipeline(i + 1, lexemes);
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else
	{
		return (0);
	}
	ft_printf(")");
	return (1 + pipeline_res);
}

int	prs_cmdinfix(int i, t_list *lexemes)
{
	int	prefix_res;
	int	current;
	int	res;

	res = 0;
	current = current_type(i, lexemes);
	while (current == LITERAL_NQ || current == LITERAL_SQ || current == LITERAL_DQ || current == REDIRLEFT || current == REDIRRIGHT || current == APPEND || current == HEREDOCOP)
	{
		ft_printf("(CmdInfix ");
		if (current == LITERAL_NQ || current == LITERAL_SQ || current == LITERAL_DQ)
		{
			prefix_res = prs_arg(i + res, lexemes);
		}
		else if (current == REDIRLEFT || current == REDIRRIGHT || current == APPEND)
		{
			prefix_res = prs_redir(i + res, lexemes);
		}
		else
		{
			prefix_res = prs_heredoc(i + res, lexemes);
		}
		if (prefix_res == -1)
			return (-1);
		ft_printf(")");
		res += prefix_res;
		current = current_type(i + res, lexemes);
	}
	return (res);
}

int	prs_pipeline(int i, t_list *lexemes)
{
	int	prefix_res;
	int	suffix_res;
	int	current;
	int	res;

	res = 0;
	ft_printf("(Pipeline ");
	current = current_type(i, lexemes);

	if (current == LPAREN)
	{
		ft_printf("(LPAREN ");
		prefix_res = prs_pipeline(i + 1, lexemes);
		//res += prefix_res;
		if (current_type(i + prefix_res + 1, lexemes) != RPAREN)
		{
			ft_printf("')' expected!");
			return (-1);
		}
		prefix_res += 2;
		ft_printf(" ENDLPAREN)");
	}
	else
	{
		prefix_res = prs_cmdinfix(i, lexemes);
	}
	if (prefix_res == -1)
	{
		return (-1);
	}

	res += prefix_res;
	suffix_res = 1;
	while (suffix_res != 0)
	{
		suffix_res = prs_suffix(i + res, lexemes);
		if (suffix_res == -1)
			return (-1);
		res += suffix_res;
	}
	ft_printf(")");
	return (res);
}

int	prs_pipelinelist (int i, t_list *lexemes)
{
	int	prs_pipelinelist_res;

	/*peek = peek_type(i, lexemes);
	if (peek == LITERAL_NQ || peek == LITERAL_SQ || peek == LITERAL_DQ)
	{
		ft_printf(" LITERAL `%s` ", (t_dict_int_str_member *) ft_lst_get(lexemes, i + 1)->content);
		peek = peek_type(i, lexemes);
		if (peek == LITERAL_NQ || peek == LITERAL_SQ || peek == LITERAL_DQ)
			return (1 + prs_cmd(i, lexemes));
		return (1);
	}*/
	prs_pipelinelist_res = 1;
	while (/*prs_pipelinelist_res != 0*/i < ft_lstsize(lexemes))
	{
		ft_printf("(PipelineList ");
		prs_pipelinelist_res = prs_pipeline(i, lexemes);
		if (prs_pipelinelist_res == -1)
		{
			ft_printf("\n");
			return (-1);
		}
		i += prs_pipelinelist_res;
		ft_printf(")");
	}
	ft_printf(")\n");
	//ft_printf("\n%sError at token %d!%s\n", RED, i, RESET);
	return (i);
}


/*t_ast_node	*lexemes_to_ast(t_list *lexemes, t_ast_node *res, int lex_pointer, int gram_pointers[2])
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
}*/
