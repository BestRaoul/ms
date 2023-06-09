#include "ms.h"

/* (cat file1 | grep '\"lol\"') && (cat file2 | grep bruh) */

int	main(void)
{
	static char	question[100] = "";
	char		*input;
	t_ast_node	*ast;

	//wildmatches("tes\\**", "/Users/jwikiera/Projets/minishell");
	ft_yoloprintf(question, "%s➜  %s", BPURPLE, WHITE);
	while (1)
	{
		ast = init_ast_node_type(PIPELINELIST);
		input = readline(question);
		//--NULLCHECK
		if (input && *input)
			add_history(input);
		//printf("%s➜  %s%s\n", BPURPLE, RESET, input);
		t_list	*lexemes = scan_tokens(input);
		//TODO: possible leak
		//replace_envvars(lexemes);
		//print_lexeme_tlist2(lexemes);
		prs_pipelinelist(0, lexemes, ast);
		//TODO free lexemes
		ft_lstclear(&lexemes, free_lexeme_node);
		ft_printf("ast:\n");
		print_ast(ast, 0);
		//EXECUTE here
		execute_pl(ast);
		free_ast(ast);
		if (strcmp(input, "exit") == 0)
			break ;
		free(input);
	}
	free(input);
	return (0);
}
