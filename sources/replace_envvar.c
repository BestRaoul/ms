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

static char	*replace_envvar_str(char *literal)
{
	char	**out;
	int		i;
	int		j;

	out = calloc((2 + 2 * count('$', literal)), sizeof(char*));
	i = 0;
	j = 0;
	while (literal[i] != '\0')
	{
		int x = find('$', &literal[i]); //-> $
		if (x < 0) { x = len(&literal[i]); } //-> 0
		if (x != 0) {
			out[j] = chop(&literal[i], x - 1);
			//--NULLCHECK
			i += len(out[j++]);
		}
		if (strncmp("$$", &literal[i], 2) == 0)
		{char pid[64]="";sprintf(pid, "%d", getpid()); out[j++] = strdup(pid);i+=2;}
		else if (literal[i] == '$')
		{
			i++; //->PATH or ->0
			char *envvar = _scan(&literal[i], is_azAZ09_);
			//--NULLCHECK
			if (getenv(envvar)) { out[j] = strdup(getenv(envvar)); } //--NULLCHECK
			else if (len(envvar) != 0) { out[j] = strdup(""); }
			else { out[j] = strdup("$"); }
			i+= len(envvar);
			j++;
		}
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
		
		if ((key == LITERAL_NQ || key == LITERAL_DQ) && prevKey != HEREDOC)
		{
			mem->value = replace_envvar_str(mem->value);
		}

		prevKey = key;
		lexemes = lexemes->next;
	}
}
