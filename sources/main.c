#include "ms.h"

/* (cat file1 | grep '\"lol\"') && (cat file2 | grep bruh) */

int	main(void)
{
	static char	question[100] = "";
	char		*input;

	wildmatches("tes\\**", "/Users/jwikiera/Projets/minishell");
	sprintf(question, "%s➜  %s", BYELLOW, WHITE);
	while (1)
	{
		input = readline(question);
		//--NULLCHECK
		if (input && *input)
			add_history(input);
		replace_env_variables(input, &input);
		printf("%s➜  %s%s\n", BPURPLE, RESET, input);
		t_list	*lexemes = scan_tokens(input);
		print_lexeme_tlist(lexemes);
		if (strcmp(input, "exit") == 0)
			break ;
		free(input);
	}
	return (0);
}
