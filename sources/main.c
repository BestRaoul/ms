#include "ms.h"

/* (cat file1 | grep '\"lol\"') && (cat file2 | grep bruh) */

extern char **environ;

t_global g = {0, 0};

int	main(void)
{
	static char	question[100] = "";
	char		*input;
	t_ast_node	*ast = NULL;

	/* env usage */
	/*char **env_copy = copy_env(environ, NULL);
	add_var_to_env("lol", "lel", &env_copy);
	remove_var_from_env("_", &env_copy);
	remove_var_from_env("_JAVA_OPTIONS", &env_copy);
	print_env(env_copy);
	fre_arr((void **) env_copy);*/

	//wildmatches("tes\\**", "/Users/jwikiera/Projets/minishell");

	g.dup_stdin = dup(STDIN_FILENO);

	ft_yoloprintf(question, "%s➜  %s", g.status==0?BBLUE:BRED, RESET);
	while (1)
	{
		ft_yoloprintf(question, "%s➜  %s", g.status==0?BBLUE:BRED, RESET);
		input = readline(question);
		//--NULLCHECK
		if (input && *input)
			add_history(input);
		else
			break ;
		t_list	*lexemes = scan_tokens(input); //?safe
		if (lexemes == NULL) break ;
		ast = parse_ast2(lexemes); //safe
		if (ast == NULL)
		{
			garbage_collector(FREE_ALL, 0);
			free(input);
			continue ;
		}
		execute_pll(ast); //safe
		if (g.status != 0)
		{	dprintf(2, "(%s%d%s) ", BRED, g.status, RESET); }
		garbage_collector(FREE_ALL, 0);
		free(input); //not FREE because not allocated via malloc
	}
	garbage_collector(FREE_ALL, 0);
	free(input);
	return (0);
}
