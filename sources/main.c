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

extern char **environ;

t_global g = {NULL, 0, 0, 0, 0};

char	*get_input()
{
	char	question[100];
	char	*input;

	ft_yoloprintf(question, "%s➜  %s", g.status==0 ? BCYAN : BRED, RESET);
	input = readline(question);
	if (input == NULL)
		return (NULL);
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

int	main(void)
{
	char		*input = NULL;
	t_ast_node	*ast = NULL;
	t_list		*lexemes = NULL;

	g.dup_stdin = dup(STDIN_FILENO);
	g.dup_stdout = dup(STDOUT_FILENO);
	g.env = realloc_strarr_no_gc(environ);
	while (1)
	{
		garbage_collector(FREE_ALL, 0);
		input = get_input(); //safe
		if (input == NULL) break;
		if (*input == 0) continue;
		lexemes = lex(input); //safe
		if (lexemes == NULL) continue;
		t_list *unwraps = unwrap(lexemes);
		if (unwraps == NULL) continue;
		ast = parse(unwraps); //safe
		if (ast == NULL) continue ;
		execute(ast); //safe
		if (g.status != 0) dprintf(2, "(%s%d%s) ", BRED, g.status, RESET);
	}
	//free g
		//close g.dup_stdin
		//reown (g.env)
	garbage_collector(FREE_ALL, 0);
	return (0);
}
