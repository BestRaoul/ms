#include "ms.h"

/* (cat file1 | grep '\"lol\"') && (cat file2 | grep bruh) */

extern char **environ;

int	main(void)
{
	static char	question[100] = "";
	char		*input;
	t_ast_node	*ast = NULL;
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
		input = readline(question);
		//--NULLCHECK
		if (input && *input)
			add_history(input);
		else
			break ;
		ft_printf("%s", RESET);
		t_list	*lexemes = scan_tokens(input);
		if (!lexemes)
			break ;
//		print_lexeme_tlist2(lexemes);
		ast = parse_ast2(lexemes);
		if (ast == NULL)//!prs_ast(lexemes, ast))
		{ 
			garbage_collector(FREE_ALL, 0);
			free(input);
			continue ;
		}
//		print_ast(ast, 0);
		//EXECUTE here
//		success_status = execute_pll(ast);
		//fre all
		garbage_collector(FREE_ALL, 0);
		free(input); //not FREE because not allocated via malloc
	}
	garbage_collector(FREE_ALL, 0);
	free(input);
	return (0);
}
