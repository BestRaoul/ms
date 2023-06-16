#include "ms.h"

/* (cat file1 | grep '\"lol\"') && (cat file2 | grep bruh) */

extern char **environ;

int	main(void)
{
	static char	question[100] = "";
	char		*input;
	t_ast_node	*ast;
	int			success_status = 0;	

	/* env usage */
	/*char **env_copy = copy_env(environ, NULL);
	add_var_to_env("lol", "lel", &env_copy);
	remove_var_from_env("_", &env_copy);
	remove_var_from_env("_JAVA_OPTIONS", &env_copy);
	print_env(env_copy);
	fre_arr((void **) env_copy);*/

	//wildmatches("tes\\**", "/Users/jwikiera/Projets/minishell");
	ft_yoloprintf(question, "%s➜  %s", success_status==0?BBLUE:BRED WHITE);
	while (1)
	{
		ft_yoloprintf(question, "%s➜  %s", success_status==0?BBLUE:BRED, WHITE);
		ast = init_ast_node_type(PIPELINELIST);
		input = readline(question);
		//--NULLCHECK
		if (input && *input && ast)
			add_history(input);
		else
			break ;
		ft_printf("%s", RESET);
		t_list	*lexemes = scan_tokens(input);
		if (!lexemes)
			break ;
		if (!prs_ast(lexemes, ast))
		{ 
			FREE(input);
			ft_lstclear(&lexemes, free_lexeme_node);
			continue ;
		}
		print_ast(ast, 0);
		//EXECUTE here
		success_status = execute_pll(ast);
		//fre all
		garbage_collector(FREE_ALL, 0);
//		ft_lstclear(&lexemes, free_lexeme_node);
//		free_ast(ast);
//		free(input); //not FREE because not allocated via malloc
	}
	garbage_collector(FREE_ALL, 0);
//	free_ast(ast);
//	free(input);
	return (0);
}
