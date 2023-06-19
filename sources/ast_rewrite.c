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

#define DEBUG_AST 0

static int	parse_pipelinelist (t_list **lexeme_ptr, t_ast_node *ast, int init);

static t_ast_node	*add_child(t_ast_node *parent, t_ast_node new)
{
	t_list		*lst_elem;
	t_ast_node	*new_node;

	lst_elem = ft_lstnew(NULL); //nc
	new_node = MALLOC(sizeof(t_ast_node)); //nc
	new_node->type = new.type;
	new_node->content = new.content;
	new_node->children = new.children;
	lst_elem->content = new_node;
	ft_lstadd_back(&(parent->children), lst_elem);
	return (new_node);
}

static int	_type(t_list *lexeme)
{
	t_dict_int_str_member *x = lexeme->content;
	return (x->key);
}

static char	*_content(t_list *lexeme)
{
	t_dict_int_str_member *x = lexeme->content;
	return (x->value);
}

static char	**_content_ptr(t_list *lexeme)
{
	t_dict_int_str_member *x = lexeme->content;
	return (&(x->value));
}


static int	peek_type(t_list *lexeme)
{
	if (lexeme->next == NULL)
		return NONE;
	return (_type(lexeme->next));
}

//assumption for parse_(arg, redir, heredoc, suffix)
//lexeme is not NULL
//type is correct

// lit nq, ', "
static int	parse_arg(t_list *lexeme, t_ast_node *ast)
{
	add_child(ast, (t_ast_node){_type(lexeme), _content(lexeme), 0});
	*_content_ptr(lexeme) = NULL;
	return 1;
}

// '>' '>>' '<'
static int	parse_redir(t_list *lexeme, t_ast_node *ast)
{
	int peek = peek_type(lexeme);

	if (peek != LITERAL_NQ && peek != LITERAL_SQ && peek != LITERAL_DQ)
		return (dprintf(2, "parse_redir: filename expected after token `%d`\n", _type(lexeme)), -1);
	add_child(ast, (t_ast_node){_type(lexeme), _content(lexeme->next), 0});
	*_content_ptr(lexeme->next) = NULL;
	return 2;
}

// '<<'
static int	parse_heredoc(t_list *lexeme, t_ast_node *ast)
{
	int peek = peek_type(lexeme);

	if (peek != LITERAL_NQ && peek != LITERAL_SQ && peek != LITERAL_DQ)
		return (dprintf(2, "parse_heredoc: delimiter expected\n"), -1);
	add_child(ast, (t_ast_node){HEREDOC, _content(lexeme->next), 0});
	*_content_ptr(lexeme->next) = NULL;
	return 2;
}

// '|' '&&' '||'
static int	parse_suffix(t_list *lexeme, t_ast_node *ast)
{
	add_child(ast, (t_ast_node){_type(lexeme), 0, 0});
	return 1;
}

// lit, redir, <<, |, '(' => pipeline_list, [')', '&&', '||'] => exit
static int	parse_pipeline(t_list **lexme_ptr, t_ast_node *ast)
{
	t_ast_node	*pipeline = add_child(ast, (t_ast_node){PIPELINE, 0, 0});
	
	int ac = 0;
	int	rc = 0;
	int	pc = 0;

	while (*lexme_ptr != NULL)
	{
		int t = _type(*lexme_ptr);
		int m = 0;

		if ((t == LITERAL_NQ || t == LITERAL_SQ || t == LITERAL_DQ) && (pc == 0))
			{ m = parse_arg(*lexme_ptr, pipeline); ac++; }
		else if (t == REDIRLEFT || t == REDIRRIGHT || t == APPEND)
			{ m = parse_redir(*lexme_ptr, pipeline); rc++; }
		else if (t == HEREDOCOP)
			{ m = parse_heredoc(*lexme_ptr, pipeline); rc++; }
		else if (t == PIPE && (ac + rc + pc > 0))
			{ m = parse_suffix(*lexme_ptr, pipeline); ac = 0; rc = 0; pc = 0;}
		else if (t == LPAREN && (ac == 0 && pc == 0))
		{ 
			*lexme_ptr = (*lexme_ptr)->next;
			m = parse_pipelinelist(lexme_ptr, pipeline, 0);
			pc++;
		}
		else if (t == AND || t == OR || t == RPAREN) break;
		else //parse ERROR 
		{
			if (ac + rc + pc == 0) break;
			return (dprintf(2, "pl: parse error 3 near unexpected `%d' token\n", _type(*lexme_ptr)), -1);
		}
		
		if (m == -1) return -1;

		*lexme_ptr = (*lexme_ptr)->next;
		if (m == 2)	*lexme_ptr = (*lexme_ptr)->next;
	}
	if (ac + rc + pc == 0)
		return (dprintf(2, "pl: missing tokens\n"), -1); // heredoc handle here
	return 0;
}

// pipeline, `&&' or `||'
static int	parse_pipelinelist(t_list **lexme_ptr, t_ast_node *ast, int init)
{
	t_ast_node	*pipeline_list;
	if (init) pipeline_list = ast;
	else pipeline_list = add_child(ast, (t_ast_node){PIPELINELIST, 0, 0});

	if (*lexme_ptr == NULL) return (dprintf(2, "pl_list: missing tokens\n"), -1);
	while (*lexme_ptr != NULL)
	{
		if (parse_pipeline(lexme_ptr, pipeline_list) == -1) return -1;
		if (*lexme_ptr == NULL)
		{
			if (init) return 0;
			return (dprintf(2, "pl_list: missing closing `)' token\n"), -1);
		}
		int t = _type(*lexme_ptr);
		if (t == AND || t == OR) 
		{
			if ((*lexme_ptr)->next == NULL) return (dprintf(2, "pl_list: missing token after `%d' token\n", _type(*lexme_ptr)), -1);
			parse_suffix(*lexme_ptr, pipeline_list);
		}
		else if (t == RPAREN && !init) return 0;
		else return (dprintf(2, "pl_list: WUT? parse error near unxepected `%d' token\n", _type(*lexme_ptr)), -1);

		*lexme_ptr = (*lexme_ptr)->next;
	}
	return 0;
}

t_ast_node	*parse(t_list *lexemes)
{
	t_ast_node *ast = MALLOC(sizeof(t_ast_node));
	ast->children = NULL;
	ast->content = NULL;
	ast->type = PIPELINELIST;

	t_list **lexme_ptr = &lexemes;
	int res = parse_pipelinelist(lexme_ptr, ast, 1);
	if (res == -1) { /*print_ast(ast, 0);*/ return (NULL); }

	t_list *lexme = *lexme_ptr;
	if (lexme && lexme->next)
		return (dprintf(2, "parse: WUT? Error trailing tokens %s->%s!",
			_content(lexme), _content(lexme->next)), NULL);
	return (ast);
}
