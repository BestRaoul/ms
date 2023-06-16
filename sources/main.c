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
	free_arr((void **) env_copy);*/

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
		//replace_envvars(lexemes);
		//print_lexeme_tlist2(lexemes);
		//if (prs_pipelinelist(0, lexemes, ast, 1) == -1)
		if (!prs_ast(lexemes, ast))
			continue ;
		ft_lstclear(&lexemes, free_lexeme_node);
//		ft_printf("ast:\n");
		replace_env_ast(ast, NULL, 0);
		print_ast(ast, 0);
		//EXECUTE here
		success_status = execute_pll(ast);
		free_ast(ast);
		free(input);
	}
	free_ast(ast);
	free(input);
	return (0);
}
