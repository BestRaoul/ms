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

int	is_leaf(t_ast_node *ast_node)
{
	if (ast_node == NULL)
		return (0);
	return (ft_lstsize(ast_node->children) == 0);
}

t_ast_node	*init_ast_node(int type, t_dict_int_str_member *lexeme)
{
	t_ast_node	*res;

	res = malloc(sizeof(*res));
	if (!res || !lexeme)
		return (NULL);
	res->content = malloc(sizeof(*res->content) * (ft_strlen(lexeme->value) + 1));
	if (!res->content)
	{
		free (res);
		return (NULL);
	}
	ft_memcpy(res->content, lexeme->value, ft_strlen(lexeme->value) + 1);
	if (type == NONE)
		res->type = lexeme->key;
	else
		res->type = type;
	res->children = NULL;
	return (res);
}

t_ast_node	*init_ast_node_type(int type)
{
	t_ast_node	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->content = NULL;
	res->type = type;
	res->children = NULL;
	return (res);
}

int	add_ast_child(t_ast_node *ast, int type, t_dict_int_str_member *lexeme)
{
	t_ast_node	*node;
	t_list		*lst_elem;

	lst_elem = ft_lstnew(NULL);
	if (!lst_elem)
		return (0);
	if (lexeme == NULL)
		node = init_ast_node_type(type);
	else
		node = init_ast_node(type, lexeme);
	if (node == NULL) {
		free(lst_elem);
		return (0);
	}
	lst_elem->content = node;
	ft_lstadd_back(&(ast->children), lst_elem);
	return (1);
}

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

int	prs_arg(int i, t_list *lexemes, t_ast_node *ast)
{
	int		current;

	(void) ast;
	current = current_type(i, lexemes);
	if (current == LITERAL_NQ || current == LITERAL_SQ || current == LITERAL_DQ)
	{
		if (!add_ast_child(ast, NONE, ft_lst_get(lexemes, i)->content))
			return (-1);
		ft_printf("(CmdArg `%s`)", ((t_dict_int_str_member *) ft_lst_get(lexemes, i)->content)->value);
		return (1);
	}
	printf("Error, expected command or command argument");
	return (-1);
}

int	prs_heredoc(int i, t_list *lexemes, t_ast_node *ast)
{
	(void) ast;
	if (peek_type(i, lexemes) != LITERAL_NQ || peek_type(i, lexemes) != LITERAL_NQ || peek_type(i, lexemes) != LITERAL_NQ)
	{
		ft_printf("Heredoc delimiter expected!");
		return (-1);
	}
	if (!add_ast_child(ast, NONE, ft_lst_get(lexemes, i)->content))
		return (-1);
	ft_printf("(Heredoc %s)", ((t_dict_int_str_member *) ft_lst_get(lexemes, i + 1)->content)->value);
	return (2);
}

int	prs_redir(int i, t_list *lexemes, t_ast_node *ast)
{
	int		peek;
	int		current;
	char	*redir_str;
	int		argres;

	current = current_type(i, lexemes);
	redir_str = ">>";
	if (current == REDIRLEFT)
	{
		redir_str = "<";
		if (!add_ast_child(ast, REDIRLEFT, NULL))
			return (-1);
	}
	else if (current == REDIRRIGHT)
	{
		redir_str = ">";
		if (!add_ast_child(ast, REDIRRIGHT, NULL))
			return (-1);
	}
	else
	{
		if (!add_ast_child(ast, APPEND, NULL))
			return (-1);
	}
	peek = peek_type(i, lexemes);
	if (peek == LITERAL_NQ || peek == LITERAL_SQ || peek == LITERAL_DQ)
	{
		ft_printf("(Redir %s ", redir_str);
		argres = prs_arg(i + 1, lexemes, ast);
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

int	prs_suffix(int i, t_list *lexemes, t_ast_node *ast)
{
	int	current;
	int	pipeline_res;

	current = current_type(i, lexemes);
	if (current == PIPE)
	{
		if (!add_ast_child(ast, PIPE, NULL))
			return (-1);
		ft_printf("(Suffix | ");
		pipeline_res = prs_pipeline(i + 1, lexemes, ast, 1);
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else if (current == AND)
	{
		if (!add_ast_child(ast, AND, NULL))
			return (-1);
		ft_printf("(Suffix && ");
		pipeline_res = prs_pipeline(i + 1, lexemes, ast, 1);
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else if (current == OR)
	{
		if (!add_ast_child(ast, OR, NULL))
			return (-1);
		ft_printf("(Suffix || ");
		pipeline_res = prs_pipeline(i + 1, lexemes, ast, 1);
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

int	prs_cmdinfix(int i, t_list *lexemes, t_ast_node *ast)
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
			prefix_res = prs_arg(i + res, lexemes, ast);
		}
		else if (current == REDIRLEFT || current == REDIRRIGHT || current == APPEND)
		{
			prefix_res = prs_redir(i + res, lexemes, ast);
		}
		else
		{
			prefix_res = prs_heredoc(i + res, lexemes, ast);
		}
		if (prefix_res == -1)
			return (-1);
		ft_printf(")");
		res += prefix_res;
		current = current_type(i + res, lexemes);
	}
	return (res);
}

int	prs_pipeline(int i, t_list *lexemes, t_ast_node *ast, int continued)
{
	int	prefix_res;
	int	suffix_res;
	int	current;
	int	res;

	res = 0;
	//TODO: add pipeline child to ast here
	// the continued var should make it append to previous pipeline
	if (!continued && !add_ast_child(ast, PIPELINE, NULL))
		return (-1);
	ft_printf("(Pipeline ");
	current = current_type(i, lexemes);

	if (current == LPAREN)
	{
		ft_printf("(LPAREN ");
		//TODO: everywhere where *ast is passed, it should sometimes be passed as some child of the current ast!!!
		//It's code to be corrected
		prefix_res = prs_pipeline(i + 1, lexemes, ast, 0); //here we give the same ast tho, because it's another pipeline
		if (current_type(i + prefix_res + 1, lexemes) != RPAREN)
		{
			ft_printf("Closing parenthesis (')') expected!");
			return (-1);
		}
		prefix_res += 2;
		ft_printf(" ENDLPAREN)");
	}
	else
	{
		prefix_res = prs_cmdinfix(i, lexemes, ft_lstlast(ast->children)->content);
	}
	if (prefix_res == -1)
	{
		return (-1);
	}

	res += prefix_res;
	suffix_res = 1;
	while (suffix_res != 0)
	{
		suffix_res = prs_suffix(i + res, lexemes, ast);
		if (suffix_res == -1)
			return (-1);
		res += suffix_res;
	}
	ft_printf(")");
	return (res);
}

int	prs_pipelinelist (int i, t_list *lexemes, t_ast_node *ast)
{
	int	prs_pipelinelist_res;

	ft_printf("(PipelineList ");
	prs_pipelinelist_res = prs_pipeline(i, lexemes, ast, 0);
	if (prs_pipelinelist_res == -1)
	{
		ft_printf("\n");
		return (-1);
	}
	i += prs_pipelinelist_res;
	if (i < ft_lstsize(lexemes))
	{
		ft_printf("Error, trailing tokens\n");
		return (-1);
	}
	ft_printf(")\n");
	//ft_printf("\n%sError at token %d!%s\n", RED, i, RESET);
	return (i);
}
