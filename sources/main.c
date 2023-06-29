/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2023/06/29 15:55:54 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

/* (cat file1 | grep '\"lol\"') && (cat file2 | grep bruh) */

extern char	**environ;

t_global	g_ = {NULL, 0, 0, 0, 0, NULL, 0, (struct termios){0}};

static char	*get_input(void)
{
	char	question[100];
	char	*input;
	char	*color;

	color = BBLUE;
	if (g_.status)
		color = BRED;
	if (g_.status != 0)
		ft_yoloprintf(question, "(%s%d%s)%s➜  %s",
			BRED, g_.status, RESET, color, RESET);
	else
		ft_yoloprintf(question, "%s➜  %s", color, RESET);
	g_.is_sig = -1;
	input = readline(question);
	g_.is_sig = 0;
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

void	init(void)
{
	struct sigaction	sa_c;
	struct sigaction	sa_slash;
	struct termios		new_termios;

	g_.dup_stdin = dup(STDIN_FILENO);
	g_.dup_stdout = dup(STDOUT_FILENO);
	g_.env = realloc_strarr_no_gc(environ);
	sa_c.sa_flags = SA_SIGINFO;
	sa_c.sa_sigaction = handler_c;
	sigemptyset(&sa_c.sa_mask);
	if (sigaction(SIGINT, &sa_c, NULL) == -1)
		crash();
	sa_slash.sa_flags = SA_SIGINFO;
	sa_slash.sa_sigaction = handler_slash;
	sigemptyset(&sa_slash.sa_mask);
	if (sigaction(SIGQUIT, &sa_slash, NULL) == -1)
		crash();
	if (tcgetattr(STDIN_FILENO, &g_.orig_termios) == -1)
		crash();
	new_termios = g_.orig_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
		crash();
}

int	main(void)
{
	char		*input;
	t_list		*lexemes;
	t_list		*unwraps;
	t_ast_node	*ast;

	init();
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
	}
}
