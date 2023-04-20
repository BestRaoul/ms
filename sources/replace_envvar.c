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

void	replace_env_variables(char *input, char **input2)
{
	char	**out;
	int		i;
	int		j;

	out = calloc((2 + 2 * count('$', input)), sizeof(char*));
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		int x = find('$', &input[i]); //-> $
		if (x < 0) { x = len(&input[i]); } //-> 0
		if (x != 0) {
			out[j] = chop(&input[i], x - 1);
			//--NULLCHECK
			i += len(out[j++]);
		}
		if (strncmp("$$", &input[i], 2) == 0)
		{char pid[64]="";sprintf(pid, "%d", getpid()); out[j++] = strdup(pid);i+=2;}
		else if (input[i] == '$')
		{
			i++; //->PATH or ->0
			char *envvar = _scan(&input[i], is_azAZ09_);
			//--NULLCHECK
			if (getenv(envvar)) { out[j] = strdup(getenv(envvar)); } //--NULLCHECK
			else if (len(envvar) != 0) { out[j] = strdup(""); }
			else { out[j] = strdup("$"); }
			i+= len(envvar);
			j++;
		}
	}
	out[j] = NULL;
	*input2 = join(out, ""); //frees
}
