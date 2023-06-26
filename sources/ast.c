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
#define EMSG "ms: ast parser: "

//for self reference
static int	parse_pipelinelist(t_list **lexeme_ptr, t_ast_node *ast, int init);

typedef struct s_pipeline_data {
	t_ast_node	*pipeline;
	int			ac;
	int			rc;
	int			pc;
	int			t;
	int			m;
}	t_pipeline_data;

//sorry for this unreadable mess, but NORM
static int	parse_pipeline_switch(t_pipeline_data *d_, t_list **lexme_ptr)
{
	if ((d_->t == LITERAL) && (d_->pc == 0) && ++d_->ac)
		d_->m = parse_arg(*lexme_ptr, d_->pipeline);
	else if (d_->t == HEREDOC && ++d_->rc)
		d_->m = parse_heredoc(*lexme_ptr, d_->pipeline);
	else if (is_redir(d_->t) && ++d_->rc)
		d_->m = parse_redir(*lexme_ptr, d_->pipeline);
	else if (d_->t == PIPE && (d_->ac + d_->rc + d_->pc > 0))
		*d_ = (t_pipeline_data){d_->pipeline, 0, 0, 0, 0,
			parse_suffix(*lexme_ptr, d_->pipeline)};
	else if (d_->t == LPAREN && (d_->ac == 0 && d_->pc == 0))
	{
		*lexme_ptr = (*lexme_ptr)->next;
		d_->m = parse_pipelinelist(lexme_ptr, d_->pipeline, 0);
		d_->pc++;
	}
	else if (d_->t == AND || d_->t == OR || d_->t == RPAREN)
		return (1);
	else
	{
		if (d_->ac + d_->rc + d_->pc == 0)
			return (1);
		return (ft_dprintf(2, EMSG"(2) error near unexpected `%s' token\n",
				_type_str(*lexme_ptr)), -1);
	}
	return (0);
}

// lit, redir, <<, |, '(' => pipeline_list, [')', '&&', '||'] => exit
static int	parse_pipeline(t_list **lexme_ptr, t_ast_node *ast)
{
	t_pipeline_data	d_;
	int				x;

	d_ = (t_pipeline_data){add_child(ast, (t_ast_node){PIPELINE, 0, 0}),
		0, 0, 0, 0, 0};
	while (*lexme_ptr != NULL)
	{
		d_.t = _type(*lexme_ptr);
		x = parse_pipeline_switch(&d_, lexme_ptr);
		if (x == 1)
			break ;
		if (x == -1)
			return (-1);
		if (d_.m == -1)
			return (-1);
		next(lexme_ptr);
		if (d_.m == 2)
			next(lexme_ptr);
	}
	if (d_.ac + d_.rc + d_.pc == 0)
		return (ft_dprintf(2, EMSG"(3) missing tokens\n"), -1);
	return (0);
}

//0 or -1 => return
//1 => next
static int	parse_pipelinelist_internal(t_list **lexme_ptr,
	t_ast_node	*pipeline_list, int t, int init)
{
	if (parse_pipeline(lexme_ptr, pipeline_list) == -1)
		return (-1);
	if (*lexme_ptr == NULL)
	{
		if (init)
			return (0);
		return (ft_dprintf(2, EMSG"(5) missing closing `)' token\n"), -1);
	}
	t = _type(*lexme_ptr);
	if (t == AND || t == OR)
	{
		if ((*lexme_ptr)->next == NULL)
			return (ft_dprintf(2, EMSG"(6) missing token after `%s' token\n",
					_type_str(*lexme_ptr)), -1);
		parse_suffix(*lexme_ptr, pipeline_list);
	}
	else if (t == RPAREN && !init)
		return (0);
	else
		return (ft_dprintf(2, EMSG
				"(7) syntax error near unxepected `%s' token\n",
				_type_str(*lexme_ptr)), -1);
	return (1);
}

// pipeline, `&&' or `||'
static int	parse_pipelinelist(t_list **lexme_ptr, t_ast_node *ast, int init)
{
	t_ast_node	*pipeline_list;
	int			x;

	if (init)
		pipeline_list = ast;
	else
		pipeline_list = add_child(ast, (t_ast_node){PIPELINELIST, 0, 0});
	if (*lexme_ptr == NULL)
		return (ft_dprintf(2, EMSG"(4) missing tokens\n"), -1);
	while (*lexme_ptr != NULL)
	{
		x = parse_pipelinelist_internal(lexme_ptr, pipeline_list, 0, init);
		if (x == 0 || x == -1)
			return (x);
		next(lexme_ptr);
	}
	return (0);
}

t_ast_node	*parse(t_list *lexemes)
{
	t_ast_node	*ast;
	t_list		**lexme_ptr;
	t_list		*lexme;

	ast = gc_malloc(sizeof(t_ast_node));
	ast->children = NULL;
	ast->content = NULL;
	ast->type = PIPELINELIST;
	lexme_ptr = &lexemes;
	if (parse_pipelinelist(lexme_ptr, ast, 1) == -1)
		return (NULL);
	lexme = *lexme_ptr;
	if (lexme && lexme->next)
		return (ft_dprintf(2, EMSG
				"(8) syntax error near unexpected token `%s'\n",
				_type_str(lexme->next)), NULL);
	if (g_.print_ast)
	{
		print_ast(ast, 0);
		g_.print_ast = 0;
	}
	return (ast);
}
