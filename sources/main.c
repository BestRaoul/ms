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
		if (input && *input && ast)
			add_history(input);
		else
			break ;
		//printf("%s➜  %s%s\n", BPURPLE, RESET, input);
		t_list	*lexemes = scan_tokens(input);
		if (!lexemes)
			break ;
		//TODO: possible leak
		//replace_envvars(lexemes);
		//print_lexeme_tlist2(lexemes);
		prs_pipelinelist(0, lexemes, ast);
		ft_lstclear(&lexemes, free_lexeme_node);
		ft_printf("ast:\n");
		print_ast(ast, 0);
		//EXECUTE here
		t_ast_node *first_child = (t_ast_node *)(ft_lst_get(ast->children, 0)->content);
		ms_execute(first_child); //0 cause we know first child is pipeline
		free_ast(ast);
		if (strcmp(input, "exit") == 0)
			break ;
		free(input);
	}
	free_ast(ast);
	free(input);
	return (0);
}
