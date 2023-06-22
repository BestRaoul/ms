/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <pkondrac@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by pkondrac          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG SHELL_MSG""
#define	DEBUG_INIT 0
#define DEBUG_REDIR 0
#define DEBUG_ARGV 0

#define IS_REDIR(x) (x == REDIRLEFT || x == REDIRRIGHT || x == APPEND)

typedef struct s_redir {
	int		type;
	char	*val;
} t_redir;

typedef struct s_parenthesis
{
	int type;
	t_list *children;
} t_parenthesis;


void	set_g_status(int err)
{
	g.status = WIFEXITED(err) ? WEXITSTATUS(err) : err;
}

void	reown(char **strr)
{
	int	i = 0;
	garbage_collector(ADD, strr);
	while (strr[i])
		garbage_collector(ADD, strr[i++]);
}

void	close_all_pipes(t_list *ignore, int crash);
void	close_and_free_all()
{
	if (g.redirs != NULL)
		close_all_pipes(NULL, 0);
	close(g.dup_stdin);
	close(g.dup_stdout);
	reown(g.env);
	garbage_collector(FREE_ALL, 0);
}

void	crash()
{
	int err = errno;
	close_and_free_all();
	errno = err;
	perror(ERROR_MSG);
	exit(err);
}

void	free_t_redir(void *ptr)
{
	if (ptr == NULL) return;
	if (((t_redir *)ptr)->val != NULL)
		FREE(((t_redir *)ptr)->val);
	FREE(ptr);
}

//ENS
t_ast_node	*get_child(t_ast_node	*node, int i)
{
	t_list	*temp = ft_lst_get(node->children, i);
	if (temp == NULL) return (NULL);
	return (temp->content);
}

//ENS
t_redir	*get_redir(t_list	*redir, int i)
{
	t_list	*temp = ft_lst_get(redir, i);
	if (temp == NULL) return (NULL);
	return (temp->content);
}

//ENS
int	count_child_pipes(t_ast_node *ast)
{
	int	i = 0;
	int	c = 0;

	t_ast_node	*child = get_child(ast, i++);
	while (child != NULL)
	{
		c += child->type == PIPE;
		child = get_child(ast, i++);
	}
	return (c);
}

//ENS
//IGNORE own pipes as they are closed during consume_redir
void	close_all_pipes(t_list *ignore, int do_crash)
{
	int redir_i;
	t_redir *r;


	int	i = 0;
	while (g.redirs[i] != NULL)
	{
		if (g.redirs[i] != ignore)
		{
			redir_i = 0;
			r = get_redir(g.redirs[i], redir_i++);
			while (r != NULL)
			{
				if (r->type == HEREDOC || r->type == PIPE_IN || r->type == PIPE_OUT)
					if (close(ft_atoi(r->val)) == -1)
					{
						if (do_crash) crash();
					}
				r = get_redir(g.redirs[i], redir_i++);
			}
		}
		i++;
	}
	g.redirs = NULL;
}

//not es
void	print_argvs(char ***argvs, int p_count)
{
	for (int k=0; k<p_count; k++)
	{
		printf("argv: [");
		int l=0;
		char **_argv = argvs[k];
		while (_argv[l] != NULL)
			printf("%s, ", _argv[l++]);
		printf("\b\b] argc: %d\n", l);
	}
}

//not es
void	print_argv(char **argv)
{
	int	arg_i = 0;
	printf("[%s", RED);
	while (argv[arg_i] != NULL)	printf("%s, ", argv[arg_i++]);
	printf("\b\b%s]\n", RESET);
}

//not es
void	print_redirs(t_list *redirs)
{
	int	redir_i = 0;
	t_redir *r = get_redir(redirs, redir_i++);
	printf("[%s", r ? "" : "  ");
	while (r != NULL)
	{
		printf("%s", BPURPLE);
		if (r->type == REDIRRIGHT) printf(">");
		if (r->type == APPEND) printf(">>");
		if (r->type == REDIRLEFT) printf("<");
		if (r->type == HEREDOC) printf("<<");
		if (r->type == PIPE_IN) printf("<|");
		if (r->type == PIPE_OUT) printf(">|");
		printf("%s%s%s%s, ", RESET, CYAN, r->val, RESET);
		r = get_redir(redirs, redir_i++);
	}
	printf("\b\b%s]\n", RESET);
}

//ENS
int	arg_count(char **argv)
{
	int	i = 0;
	while (argv[i] != NULL)
		i++;
	return i;
}

//ENS
//can fail SC -1 -> crash
int	heredoc_handler(char *delimiter)
{
	int	previous_in = dup(STDIN_FILENO);
	if (previous_in == -1) return -1;
	if (dup2(g.dup_stdin, STDIN_FILENO) == -1) return -1;

	char	*input;
	int		_pipe[2];

	if (pipe(_pipe) == -1) return -1;
	input = readline("|> "); //nc - done
	while (input != NULL && ft_strncmp(input, delimiter, len(input)) != 0)
	{
		if (write(_pipe[1], input, ft_strlen(input)) == -1
			|| write(_pipe[1], "\n", 1) == -1)
			return -1;
		free(input);
		input = readline("|> ");//nc - done
	}
	if (input == NULL) ft_dprintf(2, ERROR_MSG"warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
	free(input);
	if (close(_pipe[1]) == -1) return -1;
	if (dup2(previous_in, STDIN_FILENO) == -1) return -1;
	return _pipe[0];
}

//ENS
char	***alloc_argvs(t_ast_node *ast, int pipe_count)
{
	char		***argvs;
	t_ast_node	*child;
	int			literal_c;
	int			i;
	int			j;

	i = 0;
	child = get_child(ast, i++);
	argvs = ft_calloc(pipe_count + 1, sizeof(char **));
	literal_c = 0;
	j = 0;
	while (child != NULL)
	{
		literal_c += (child->type == LITERAL);
		if (child->type == PIPE)
		{
			argvs[j++] = ft_calloc(literal_c + 1, sizeof(char *));
			literal_c = 0;
		}
		child = get_child(ast, i++);
	}
	argvs[j++] = ft_calloc(literal_c + 1, sizeof(char *));
	argvs[j] = NULL;
	return (argvs);
}

//ENS
t_list	*alloc_redir(int type, char *val)
{
	if (val == NULL)
		return NULL;
	t_redir *redir = MALLOC(sizeof(t_redir)); //nc
	redir->type = type;
	redir->val = val;
	t_list *_redir = ft_lstnew(redir); //nc =>free
	return _redir;
}

//ENS
//SC fail -1 -> crash
//returns errno if failed to consume access redir
int	consume_redirs(t_list *redirs)
{
	int	redir_i = 0;
	t_redir *r = get_redir(redirs, redir_i++);

	int	in_i = -1;
	int	out_i = -1;
	//first pass to set in_i and out_i, -1 means unset
	while (r != NULL)
	{
		if (r->type == REDIRLEFT || r->type == HEREDOC || r->type == PIPE_IN)
			in_i = redir_i;
		else if (r->type == REDIRRIGHT || r->type == APPEND)
			out_i = redir_i;
		else if (r->type == PIPE_OUT && out_i == -1)
			out_i = redir_i;
		r = get_redir(redirs, redir_i++);
	}
	if (DEBUG_REDIR)
	{printf("[%d] %.0d > %.0d\n", getpid(), in_i != -1 ? in_i : 0, out_i != -1 ? out_i : 0);}

	//second pass to just create the files unused and close pipes unused
	redir_i = 0;
	r = get_redir(redirs, redir_i++);
	while (r != NULL)
	{
		if (redir_i != in_i && redir_i != out_i && r->type != PARENTHESIS)
		{
			int temp_fd = -1;
			if (r->type == REDIRRIGHT || r->type == APPEND)
				temp_fd = open(r->val, O_CREAT | O_WRONLY | O_TRUNC, (unsigned int)00664);
			else if (r->type == REDIRLEFT)
				temp_fd = access(r->val, R_OK);
			else if (r->type == HEREDOC || r->type == PIPE_IN || r->type == PIPE_OUT)
				temp_fd = ft_atoi(r->val);

			if (r->type == REDIRLEFT && temp_fd == -1)
			{
				int err = errno;
				return (ft_dprintf(2, ERROR_MSG"%s: %s\n", r->val, strerror(err)), err);
			}
			if (temp_fd == -1) return -1;
			if (close(temp_fd) == -1) return -1;
		}
		r = get_redir(redirs, redir_i++);
	}

	//last pass to setup the redirects
	redir_i = 0;
	r = get_redir(redirs, redir_i++);
	while (r != NULL)
	{
		if (redir_i == in_i || redir_i == out_i)
		{
			int	to = 0, from = 0;
			if (r->type == REDIRRIGHT)
			{
				to = open(r->val, O_WRONLY | O_CREAT | O_TRUNC, (unsigned int)00664);
				from = STDOUT_FILENO;
			}
			if (r->type == APPEND)
			{
				to = open(r->val, O_WRONLY | O_CREAT | O_APPEND, (unsigned int)00664);
				from = STDOUT_FILENO;
			}
			if (r->type == REDIRLEFT)
			{
				to = open(r->val, O_RDONLY, (unsigned int)00664);
				from = STDIN_FILENO;
			}
			if (r->type == HEREDOC)
			{ to = ft_atoi(r->val); from = STDIN_FILENO;}
			if (r->type == PIPE_IN)
			{ to = ft_atoi(r->val); from = STDIN_FILENO;}
			if (r->type == PIPE_OUT)
			{ to = ft_atoi(r->val); from = STDOUT_FILENO;}
			
			if (IS_REDIR(r->type) && to == -1)
			{
				int err = errno;
				return (ft_dprintf(2, ERROR_MSG"%s: %s\n", r->val, strerror(err)), err);
			}
			if (to == -1) return -1;
			if (dup2(to, from) == -1) return -1;
			if (close(to) == -1) return -1;
		}
		r = get_redir(redirs, redir_i++);
	}
	return (0);
}

//ENS
//exit point -> never returns
void	execute_command(char	**argv, t_list *lst_redir, pid_t parent_pid, t_parenthesis parenthesis)
{
	if (DEBUG_INIT) {
	printf("(%s) [%s%d%s] -- spawned from %s%d%s\n", argv[0], BLUE, getpid(), RESET, GREEN, parent_pid, RESET);}
	if (DEBUG_ARGV) {
	printf("(%s) [%s%d%s] -- args ", argv[0], BLUE, getpid(), RESET);
	print_argv(argv);}
	if (DEBUG_REDIR) {
	printf("(%s) [%s%d%s] -- redir ", argv[0], BLUE, getpid(), RESET);
	print_redirs(lst_redir); }
	
	int err = consume_redirs(lst_redir);
	if (err == -1)
		crash();
	else if (err > 0)
		exit(err);
	
	close_all_pipes(lst_redir, 1);

	if (parenthesis.type == PARENTHESIS)
	{
		t_ast_node pll = (t_ast_node){PIPELINELIST, NULL, parenthesis.children};
		execute(&pll);
		close_and_free_all();
		exit(g.status);
	}
	else
	{
		if (is_builtin(argv[0]))
		{
			int status = exec_builtin(argv[0], argv);
			close_and_free_all();
			exit(status);
		}
		else
		{
			char **my_argv = realloc_strarr_no_gc(argv);
			garbage_collector(FREE_ALL, 0);
			close(g.dup_stdin);
			close(g.dup_stdout);

			char *pathname = ft_getpath(my_argv[0], g.env);
			if (pathname != NULL)
				execve(pathname, my_argv, g.env);
			ft_dprintf(2, "%s: command not found\n", my_argv[0]);
			reown(my_argv);
			close_and_free_all();
			exit(127);
		}
	}
}

//ENS
//crashes if sc fail
//always non-null return value
pid_t	*init_subshells(char ***argvs, t_parenthesis *parens, int p_count)
{
	pid_t	*pids = ft_calloc(p_count + 1, sizeof(pid_t));
	pid_t	parent = getpid();
	int	i = 0;

	while (i < p_count)
	{
		pids[i] = fork();
		if (pids[i] == -1) crash();
		if (pids[i] == 0)
			execute_command(argvs[i], g.redirs[i], parent, parens[i]);
		i++;
	}
	return pids;
}

//ENS sc
void	populate_execution_data(char ***argvs, t_parenthesis *parens, t_ast_node *pipeline)
{
	int 		arg_i = 0;
	int			pipe_i = 0;
	int			child_i = 0;
	int			_pipe[2] = {-1, -1};
	t_ast_node	*child = get_child(pipeline, child_i++); //nc - done inherently
	
	while (child != NULL)
	{	
		if (child->type == LITERAL)
		{ (argvs[pipe_i])[arg_i++] = child->content; child->content = NULL;}
		else if (IS_REDIR(child->type))
		{
			t_list	*redir = alloc_redir(child->type, child->content);
			child->content = NULL;
			ft_lstadd_back(&g.redirs[pipe_i], redir);
		}
		else if (child->type == HEREDOC)
		{
			int	fd_pipe_end = heredoc_handler(child->content);
			if (fd_pipe_end == -1) crash();
			t_list	*redir = alloc_redir(HEREDOC, ft_itoa(fd_pipe_end));
			ft_lstadd_back(&g.redirs[pipe_i], redir);
		}
		else if (child->type == PIPE)
		{ 
			if (pipe(_pipe) == -1) crash();
			ft_lstadd_back(&g.redirs[pipe_i], alloc_redir(PIPE_OUT, ft_itoa(_pipe[1])));
			pipe_i++; arg_i = 0; parens[pipe_i] = (t_parenthesis){NONE, NULL};
			ft_lstadd_back(&g.redirs[pipe_i], alloc_redir(PIPE_IN, ft_itoa(_pipe[0])));
		}
		else if (child->type == PIPELINELIST)
		{
			parens[pipe_i] = (t_parenthesis){PARENTHESIS, child->children}; 
			child->children = NULL;
		}
		else { ft_dprintf(2, "pipeline: BIG ERROR\n"); exit(127); }
		
		child = get_child(pipeline, child_i++); //nc - done
	}
}

//ENS
int	do_solo_exec_builtin(char **argv)
{
	int err = consume_redirs(g.redirs[0]);
	if (err > 0) return (err);
	if (err == -1) crash();
	int status = exec_builtin(argv[0], argv);
	if (dup2(g.dup_stdin, STDIN_FILENO) == -1) crash();
	if (dup2(g.dup_stdin, STDOUT_FILENO) == -1) crash();
	return (status);
}

void	execute(t_ast_node *pipeline_list);

//ENS
static int	execute_pipeline(t_ast_node *pipeline)
{
	char			***argvs;
	t_parenthesis	*parens;
	pid_t			*pids;
	int				pipe_count;

	//sc
	pipe_count = count_child_pipes(pipeline) + 1;
	argvs = alloc_argvs(pipeline, pipe_count);
	g.redirs = ft_calloc(pipe_count + 1, sizeof(t_list *));
	parens = ft_calloc(pipe_count + 1, sizeof(t_parenthesis));

	//sc
	populate_execution_data(argvs, parens, pipeline);

	//sc
	if (pipe_count == 1 && is_builtin(argvs[0][0]))
		return (do_solo_exec_builtin(argvs[0]));

	//sc
	pids = init_subshells(argvs, parens, pipe_count);
	
	//sc
	close_all_pipes(NULL, 1);

	int status = -42;
	for(int x=0; x<pipe_count; x++)
		if (waitpid(pids[x], &status, 0) == -1)
			crash();
	return status;
}

//ENS
void	execute(t_ast_node *pipeline_list)
{
	t_ast_node	*child;
	t_ast_node	*next;
	int			child_i;
	int			status;

	child_i = 0;
	child = get_child(pipeline_list, child_i++); //nc - done inherently
	status = 1;
	while (child != NULL)
	{
		if (status == 1)
		{
			status = execute_pipeline(child);
			set_g_status(status);
		}
		else
			status = -42;
		next = get_child(pipeline_list, child_i++); //nc - done
		if (next == NULL) break;

		if (next->type == AND)
			status = (status == 0);
		else if (next->type == OR)
			status = (status != 0);
		child = get_child(pipeline_list, child_i++); //nc - done
	}
}
