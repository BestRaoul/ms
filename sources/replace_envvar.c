#include "ms.h"

#define DEBUG_ENV 0

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

	out = calloc((2 + 2 * count('$', literal)), sizeof(char *));
	if (DEBUG_ENV) {
	printf("%s: %d\n", literal, 2 + 2 * count('$', literal));}
	j = 0;
	while (*literal)
	{
		if (strncmp("$$", literal, 2) == 0)
		{
			out[j] = handle_dd();
			if (DEBUG_ENV) {
			printf("[%d] =dd= \'%s\'\n", j, out[j]);}
			//NULLCHECK out[j]
			literal += 2;
			j++;
			continue ;
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
			if (DEBUG_ENV) {
			ft_printf("[%d] = \'%.*s\' -> ", j, x, literal);}
			out[j] = chop(literal, x - 1);
			literal+=x;
		}
		if (DEBUG_ENV) {
		printf("\'%s\'\n", out[j]);}
		//NULLCHECK out[j]
		j++;
	}
	out[j] = NULL;
	char	*result = join(out, "");
	//nc result
	//frees2(2, 1, out, 0, literal);
	frees2(1, 1, out, 0);
	return result; //frees (out)
}

int	is_export(t_ast_node *ast, int iscommand)
{
	if (!iscommand)
		return (0);
	if (ast == NULL)
		return (0);
	if (ast->content == NULL)
		return (0);
	if (ast->type != LITERAL_SQ && ast->type != LITERAL_DQ && ast->type != LITERAL_NQ)
		return (0);
	return (ft_strlen("export") == ft_strlen(ast->content) && !ft_strncmp("export", ast->content, ft_strlen("export")));
}

int	is_command(int i, t_list *children)
{
	int	literal_found;
	t_ast_node	*node;

	literal_found = -1;
	for (int j = 0; i < ft_lstsize(children); ++i) {
		node = ft_lst_get(children, j)->content;
		if (node->type == LITERAL_DQ || node->type == LITERAL_NQ || node->type == LITERAL_SQ)
		{
			literal_found = j;
			break ;
		}
	}
	return (literal_found == i);
}

int	replace_env_ast(t_ast_node *ast, t_ast_node *prev, int iscommand)
{
	char	*new_val;
	int		ret;

	ret = 1;
	if ((ast->type == LITERAL_NQ || ast->type == LITERAL_DQ) && (!prev || (prev->type != HEREDOC && !is_export(prev, iscommand))))
	{
		ft_printf("dupa0\n");
		new_val = handle_env(ast->content);
		ft_printf("dupa1\n");
		if (!new_val)
			return (0);
		free(ast->content);
		ast->content = new_val;
	}
	for (int i = 0; i < ft_lstsize(ast->children); ++i) {
		if (i == 0)
			ret = ft_min_int(replace_env_ast(ft_lst_get(ast->children, i)->content, NULL, is_command(i, ast->children)), 1);
		else
			ret = ft_min_int(replace_env_ast(ft_lst_get(ast->children, i)->content, ft_lst_get(ast->children, i - 1)->content, is_command(i, ast->children)), 1);
	}
	return (ret);
}
