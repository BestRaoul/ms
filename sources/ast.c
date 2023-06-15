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

#define DEBUG_AST 1

t_ast_node	*init_ast_node(int type, t_dict_int_str_member *lexeme)
{
	t_ast_node	*res;

	res = MALLOC(sizeof(*res));
	if (!res || !lexeme)
		return (NULL);
	res->content = MALLOC(sizeof(*res->content) * (ft_strlen(lexeme->value) + 1));
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

	res = MALLOC(sizeof(*res));
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
	//ft_printf("allocating child %p\n", lst_elem);
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

/* Like peek but backwards */
int	back_type(int i, t_list *lst)
{
	t_list	*current;

	if (i > ft_lstsize(lst))
		return (END);
	if (i == 0)
		return (FAILED);
	current = ft_lst_get(lst, i - 1);
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

	current = current_type(i, lexemes);
	if (current == LITERAL_NQ || current == LITERAL_SQ || current == LITERAL_DQ)
	{
		if (!add_ast_child(ast, NONE, ft_lst_get(lexemes, i)->content))
			return (-1);
		if (DEBUG_AST) {
		ft_printf("(CmdArg `%s`)", ((t_dict_int_str_member *) ft_lst_get(lexemes, i)->content)->value); }
		return (1);
	}
	if (DEBUG_AST) {
	printf("Error, expected command or command argument"); }
	return (-1);
}

int	prs_heredoc(int i, t_list *lexemes, t_ast_node *ast)
{
	if (!ft_lst_get(lexemes, i + 1))
		return (-1);
	if (peek_type(i, lexemes) != LITERAL_NQ && peek_type(i, lexemes) != LITERAL_NQ && peek_type(i, lexemes) != LITERAL_NQ)
	{
		if (DEBUG_AST) {
		ft_printf("Heredoc delimiter expected!"); }
		return (-1);
	}
	t_dict_int_str_member *heredocmem = t_dict_int_str_member_init(HEREDOC, ((t_dict_int_str_member *)ft_lst_get(lexemes, i + 1)->content)->value);
	if (!heredocmem)
		return (-1);
	if (!add_ast_child(ast, NONE, heredocmem))
		return (-1);
	if (DEBUG_AST) {
	ft_printf("(Heredoc %s)", ((t_dict_int_str_member *) ft_lst_get(lexemes, i + 1)->content)->value); }
	return (2);
}

int	prs_redir(int i, t_list *lexemes, t_ast_node *ast)
{
	int		peek;
	int		current;
	char	*redir_str;

	if (!ft_lst_get(lexemes, i + 1))
		return (-1);
	peek = peek_type(i, lexemes);
	if (peek != LITERAL_NQ && peek != LITERAL_SQ && peek != LITERAL_DQ)
	{
		if (DEBUG_AST) {
		ft_printf("Filename expected! "); }
		return (-1);
	}
	current = current_type(i, lexemes);
	redir_str = ">>";
	if (current == REDIRLEFT)
	{
		redir_str = "<";
		if (!add_ast_child(ast, REDIRLEFT, ft_lst_get(lexemes, i + 1)->content))
			return (-1);
	}
	else if (current == REDIRRIGHT)
	{
		redir_str = ">";
		if (!add_ast_child(ast, REDIRRIGHT, ft_lst_get(lexemes, i + 1)->content))
			return (-1);
	}
	else
	{
		if (!add_ast_child(ast, APPEND, ft_lst_get(lexemes, i + 1)->content))
			return (-1);
	}
	if (DEBUG_AST) {
	ft_printf("(Redir %s %s)", redir_str, ((t_dict_int_str_member *) ft_lst_get(lexemes, i + 1)->content)->value); }
	return (2);
}

int	prs_suffix(int i, t_list *lexemes, t_ast_node *ast)
{
	int	current;
	int	pipeline_res;
	int	redir_res;

	current = current_type(i, lexemes);
	redir_res = 0;
	if (current == PIPE)
	{
		if (!add_ast_child(ft_lstlast(ast->children)->content, PIPE, NULL))
			return (-1);
		if (DEBUG_AST) {
		ft_printf("(Suffix | "); }
		pipeline_res = prs_pipeline(i + 1, lexemes, ast, 1) + 1;
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else if (current == AND)
	{
		if (!add_ast_child(ast, AND, NULL))
			return (-1);
		if (DEBUG_AST) {
		ft_printf("(Suffix && "); }
		pipeline_res = prs_pipeline(i + 1, lexemes, ast, 0) + 1;
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else if (current == OR)
	{
		if (!add_ast_child(ast, OR, NULL))
			return (-1);
		if (DEBUG_AST) {
		ft_printf("(Suffix || "); }
		pipeline_res = prs_pipeline(i + 1, lexemes, ast, 0) + 1;
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else if (current == APPEND || current == REDIRRIGHT || current == REDIRLEFT)
	{
		redir_res = prs_redir(i, lexemes, ast);
		if (redir_res == -1)
			return (-1);
		pipeline_res = prs_suffix(i + redir_res, lexemes, ast);
		if (pipeline_res == -1)
		{
			return (-1);
		}
	}
	else
	{
		return (0);
	}
	if (DEBUG_AST) {
	ft_printf(")"); }
	return (redir_res + pipeline_res);
}

int	prs_cmdinfix(int i, t_list *lexemes, t_ast_node *ast)
{
	int	prefix_res;
	int	current;
	int	res;

	res = 0;
	current = current_type(i, lexemes);
	while (current == LITERAL_NQ || current == LITERAL_SQ || current == LITERAL_DQ || current == REDIRLEFT || current == REDIRRIGHT || current == APPEND || current == HEREDOCOP )
	{
		if (DEBUG_AST) {
		ft_printf("(CmdInfix "); }
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
		if (DEBUG_AST) {
		ft_printf(")"); }
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

	current = current_type(i, lexemes);
	if (current == LPAREN)
		return (prs_pipelinelist(i, lexemes, ft_lstlast(ast->children)->content, 0));
		//return (prs_pipelinelist(i, lexemes, ast, 0));
	res = 0;
	if (DEBUG_AST) {
	ft_printf("(Pipeline "); }
	if (!continued /*&& current != LPAREN*/ && !add_ast_child(ast, PIPELINE, NULL))
		return (-1);
	prefix_res = prs_cmdinfix(i, lexemes, ft_lstlast(ast->children)->content);
	if (prefix_res == 0)
	{
		if (DEBUG_AST) {
		ft_printf(" Empty Pipeline! "); }
		return (-1);
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
	/*if (ft_lstlast(ast->children) && ft_lstsize(((t_ast_node *)(ft_lstlast(ast->children)->content))->children) == 0)
		ft_printf("empty pipeline");*/
	if (DEBUG_AST) {
	ft_printf(")"); }
	return (res);
}

int	prs_pipelinelist (int i, t_list *lexemes, t_ast_node *ast, int init)
{
	int	prs_pipelinelist_res;

	if (DEBUG_AST) {
	ft_printf("(PipelineList "); }
	if (!init && current_type(i, lexemes) != LPAREN && !add_ast_child(ast, PIPELINELIST, NULL))
		return (-1);
	if (!init && current_type(i, lexemes) != LPAREN)
		ast = ft_lstlast(ast->children)->content;
	if (current_type(i, lexemes) == LPAREN)
	{
		if (DEBUG_AST) {
			ft_printf("(LPAREN "); }
		prs_pipelinelist_res = prs_pipelinelist(i + 1, lexemes, ast, 0);
		if (prs_pipelinelist_res == -1)
			return (-1);
		if (current_type(i + prs_pipelinelist_res + 1, lexemes) != RPAREN)
		{
			if (DEBUG_AST) {
				ft_printf("Closing parenthesis (')') expected!"); }
			return (-1);
		}
		prs_pipelinelist_res += 2;
		if (DEBUG_AST) {
			ft_printf(" ENDLPAREN)"); }
	}
	else
		return(prs_pipeline(i, lexemes, ast, 0));
	//i += prs_pipelinelist_res;
	return (prs_pipelinelist_res);
}

void	free_ast(t_ast_node *ast)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	while (i < ft_lstsize(ast->children))
	{
		free_ast(ft_lst_get(ast->children, i)->content);
		i ++;
	}
	if (ast->content)
		free(ast->content);
	if (ast->children)
		free(ast->children);
	free(ast);
	ast = NULL;
}

int	prs_ast(t_list *lexemes, t_ast_node *ast)
{
	int	res;
	res = prs_pipelinelist(0, lexemes, ast, 1);
	if (DEBUG_AST) {
		ft_printf("\n");
		ft_printf("res size: %d\n", res);
	}
	if (res == -1)
		return (0);
	if (res < ft_lstsize(lexemes))
	{
		if (DEBUG_AST) {
			ft_printf("Error, trailing tokens\n");
		}
		return (0);
	}
	return (1);
}
