#include "ms.h"

int	in(char c, char *str)
{
	if (find(c, str) != -1)
		return (1);
	return (0);
}

int	is_azAZ09_(char c)
{
	return (in(c, "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRST")
		|| in(c, "UVWXYZ0123456789"));
}

static char *handle_var(char *envvar)
{
	ft_printf("[] = \'%s\' -> ",envvar);
	if (len(envvar) == 0)
		return (strdup("$"));
	else if (getenv(envvar)) 
		return (strdup(getenv(envvar)));
	else
		return (strdup(""));	
}

static char	*handle_dd()
{
	char	pid[64]="";

	ft_yoloprintf(pid, "%d", getpid());
	return strdup(pid);
}

char	*handle_env(char *literal)
{
	char	**out;
	int		j;

	out = calloc((2 + 2 * count('$', literal)), sizeof(char*));
	printf("%s: %d\n", literal, 2 + 2 * count('$', literal));
	j = 0;
	while (*literal)
	{
		if (strncmp("$$", literal, 2) == 0)
		{
			out[j] = handle_dd();
			printf("[%d] =dd= \'%s\'\n", j, out[j]);
			//NULLCHECK
			literal+=2;
			j++;
			continue;
		}

		int x = find_noescape('$', literal);
		if (x == -1)
			x = len(literal);

		if (*literal == '$')
		{
			literal++;
			out[j] = handle_var(_scan2(&(literal), is_azAZ09_));
		}
		else
		{
			ft_printf("[%d] = \'%.*s\' -> ", j, x, literal);
			out[j] = chop(literal, x - 1);
			literal+=x;
		}
		printf("\'%s\'\n", out[j]);
		//NULLCHECK out[j]
		j++;
	}
	out[j] = NULL;
	return join(out, ""); //frees
}

void	replace_envvars(t_list *lexemes)
{
	t_dict_int_str_member *mem;
	int	prevKey;

	prevKey = -1;
	while (lexemes != NULL)
	{
		mem = (t_dict_int_str_member *) lexemes->content;
		int		key = mem->key;
		
		if ((key == LITERAL_NQ || key == LITERAL_DQ) && prevKey != HEREDOCOP)
		{
			mem->value = handle_env(mem->value);
		}

		prevKey = key;
		lexemes = lexemes->next;
	}
}
