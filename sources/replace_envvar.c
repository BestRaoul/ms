#include "ms.h"

#define DEBUG_ENV 0

int	is_azAZ09_(char c)
{
	return (in(c, "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRST")
		|| in(c, "UVWXYZ0123456789"));
}

static char	*handle_var(char *envvar)
{
	int	x;
	int	eq_i;

	if (len(envvar) == 0)
		return (ft_strdup("$"));
	x = find_in_env(envvar);
	if (x != -1)
	{
		eq_i = ft_find('=', g.env[x]);
		if (eq_i == -1) {dprintf(2, "env: no `=' in envvar WUT?\n"); exit(69); }
		return (ft_strdup(&(g.env[x][eq_i + 1])));
	}
	return (ft_strdup(""));	
}

static char	*handle_dd()
{
	char	pid[64]="";

	ft_yoloprintf(pid, "%d", getpid());
	return ft_strdup(pid);
}

static char	*handle_status()
{
	char	status[64]="";

	ft_yoloprintf(status, "%d", g.status);
	return ft_strdup(status);
}

char	*handle_env_until(char *str, int end)
{
	char	*res;
	char	temp;

	temp = str[end];
	str[end] = 0;
	res = handle_env(str);
	str[end] = temp;
	return (res);
}

char	*handle_env(char *literal)
{
	char	**out;
	int		j;

	out = ft_calloc((2 + 2 * count('$', literal)), sizeof(char *)); //nc
	j = 0;
	while (*literal)
	{
		int x = find_ne_nqs('$', literal, "\'");
		out[j] = chop(literal, x - 1); 
		literal += len(out[j]);
		j++;
		if (literal[0] == 0) break;
		if (literal[1] && literal[1] == '$')
		{
			out[j] = handle_dd();
			literal += 2;
			j++;
			continue ;
		}
		if (literal[1] && literal[1] == '?')
		{
			out[j] = handle_status();
			literal += 2;
			j++;
			continue ;
		}

		literal++;
		out[j] = handle_var(_scan2(&(literal), is_azAZ09_));
		j++;
	}
	out[j] = NULL;
	char	*result = join(out, "");
	frees2(1, 1, out, 0);
	return result;
}
