#include "ms.h"

/* (cat file1 | grep '\"lol\"') && (cat file2 | grep bruh) */

int	main(void)
{
	static char	question[100] = "";
	char		*input;

	wildmatches("tes\\**", "/Users/jwikiera/Projets/minishell");
	ft_yoloprintf(question, "%s➜  %s", BYELLOW, WHITE);
	while (1)
	{
		input = readline(question);
		//--NULLCHECK
		if (input && *input)
			add_history(input);
		printf("%s➜  %s%s\n", BPURPLE, RESET, input);
		t_list	*lexemes = scan_tokens(input);
		replace_envvars(lexemes);
		print_lexeme_tlist2(lexemes);
		if (strcmp(input, "exit") == 0)
			break ;
		free(input);
	}
	free(input);
	return (0);
}
