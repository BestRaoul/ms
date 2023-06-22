/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 12:42:36 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

/* (cat file1 | grep '\"lol\"') && (cat file2 | grep bruh) */

extern char	**environ;

t_global	g_ = {NULL, 0, 0, 0, 0, NULL};

static char	*get_input(void)
{
	char	question[100];
	char	*input;
	char	*color;

	color = BBLUE;
	if (g_.status)
		color = BRED;
	ft_yoloprintf(question, "%s➜  %s", color, RESET);
	input = readline(question);
	if (input == NULL)
		exit_builtin(NULL);
	garbage_collector(ADD, input);
	if (*input == 0)
		return (input);
	add_history(input);
	return (input);
}

void	print_tlst(t_list *iter)
{
	while (iter)
	{
		printf("%s   ", (char *)iter->content);
		iter = iter->next;
	}
}

void	init_g(void)
{
	g_.dup_stdin = dup(STDIN_FILENO);
	g_.dup_stdout = dup(STDOUT_FILENO);
	g_.env = realloc_strarr_no_gc(environ);
}

int	main(void)
{
	char		*input;
	t_list		*lexemes;
	t_list		*unwraps;
	t_ast_node	*ast;

	init_g();
	while (1)
	{
		garbage_collector(FREE_ALL, 0);
		input = get_input();
		if (*input == 0)
			continue ;
		lexemes = lex(input);
		unwraps = unwrap(lexemes);
		if (unwraps == NULL)
			continue ;
		ast = parse(unwraps);
		if (ast == NULL)
			continue ;
		execute(ast);
		if (g_.status != 0)
			ft_dprintf(2, "(%s%d%s) ", BRED, g_.status, RESET);
	}
	close_and_free_all();
	return (0);
}
