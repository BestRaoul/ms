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

#define ERROR_MSG "ms_turtle"
#define	DEBUG_INIT 0
#define DEBUG_REDIR 0
#define DEBUG_ARGV 0

void	xit()
{
	int err = errno;
	perror(ERROR_MSG);
	exit(err);
}

void	xit2(int err)
{
	errno = err;
	perror(ERROR_MSG);
	exit(err);
}

//pl{}, ., pl{}, ., pl{}...
/*pl{
	a |
	b |
	()|
	...
}*/

//(pl{}, ., pl{}, ., pl{}...)

/* TODO but better
	1. pipeline node and &&/|| handling
	- PARENTHESIS -> pretty much
	. (ls)
	. ((ls))
	2. error management
	- execution
	. lexing
	. ++main..
3. nullchecks
	. inside garbage collector
4. garbage collector
5. builtins (echo -n, cd, pwd, export, unset, env, exit)
6. env management
7. var replacement and $? status
8. wildcards
*/

#define IS_LITERAL(x) (x == LITERAL_NQ || x == LITERAL_SQ || x == LITERAL_DQ)
#define IS_REDIR(x) (x == REDIRLEFT || x == REDIRRIGHT || x == APPEND)

typedef struct s_redir {
	int		type;
	char	*val;
} t_redir;

typedef	struct s_free {
	char	***argvs;
	t_list	**redirs;
	int		p_count;
} t_free;

typedef struct s_parenthesis
{
	int type;
	t_list *children;
} t_parenthesis;

void	free_t_redir(void *ptr)
{
	if (ptr == NULL) return;
	if (((t_redir *)ptr)->val != NULL)
		FREE(((t_redir *)ptr)->val);
	FREE(ptr);
}

t_ast_node	*get_child(t_ast_node	*node, int i)
{
	t_list	*temp = ft_lst_get(node->children, i);
	if (temp == NULL) return (NULL);
	return (temp->content);
}

t_redir	*get_redir(t_list	*redir, int i)
{
	t_list	*temp = ft_lst_get(redir, i);
	if (temp == NULL) return (NULL);
	return (temp->content);
}

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

//es
void	close_pipes(t_list *redirs)
{
	int	redir_i = 0;
	t_redir *r = get_redir(redirs, redir_i++);
	while (r != NULL)
	{
		if (r->type == HEREDOC || r->type == PIPE_IN || r->type == PIPE_OUT)
			if (close(ft_atoi(r->val)) == -1) xit();
		r = get_redir(redirs, redir_i++);
	}
}

//es
void	close_all_pipes(t_list **redirs, t_list *ignore)
{
	int	i = 0;
	while (redirs[i] != NULL)
	{
		if (redirs[i] != ignore)
			close_pipes(redirs[i]->next);
		i++;
	}
}

//not es
void	print_open_fds(int	max, int fd)
{
	int	i = 0;
	dprintf(fd, "[%d] fds: [", getpid());
	while (i < max)
	{
		int is = fcntl(i, F_GETFL);
		dprintf(fd, "%s%s%s, ", is!=-1?GREEN:RED, is!=-1?"y":"x", RESET);
		i++;
	}
	dprintf(fd, "\b\b]\n");
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

int	arg_count(char **argv)
{
	int	i = 0;
	while (argv[i] != NULL)
		i++;
	return i;
}

//es
int	heredoc_handler(char *delimiter)
{
	char	*input;
	int		_pipe[2];

	if (pipe(_pipe) == -1) xit();
	input = readline("|> ");//nc
	while (input != NULL && strcmp(input, delimiter) != 0)
	{
		if (write(_pipe[1], input, ft_strlen(input)) == -1
			|| write(_pipe[1], "\n", 1) == -1)
			xit();
		free(input);
		input = readline("|> ");//nc
	}
	//if (input == NULL) xit();
	if (close(_pipe[1]) == -1) xit();
	return _pipe[0];
}

char	***alloc_argvs(t_ast_node *ast, int p_count)
{
	int	i = 0;
	int	j = 0;
	t_ast_node	*child = get_child(ast, i++);
//	printf("argv's: %d\n", count_child_pipes(ast) + 1);
	char ***argvs = ft_calloc(p_count + 1, sizeof(char **)); //nc
	int literal_c = 0;
	while (child != NULL)
	{
		literal_c += (IS_LITERAL(child->type));
		if (child->type == PIPE)
		{
//			printf("(%d)-th argv: %d\n", j, literal_c + 1);
			argvs[j++] = ft_calloc(literal_c + 1, sizeof(char *)); //nc
			literal_c = 0;
		}
		child = get_child(ast, i++);
	}
//	printf("(%d)-th argv: %d\n", j, literal_c + 1);
	argvs[j++] = ft_calloc(literal_c + 1, sizeof(char *));
	argvs[j] = NULL;
	return (argvs);
}

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

t_list	**init_redirs(int p_count)
{
	t_list **redirs = ft_calloc(p_count + 1, sizeof(t_list *)); //nc
	int	i = 0;

	while (i < p_count)
	{
		redirs[i] = ft_lstnew(NULL); //nc
		i++;
	}
	redirs[i] = NULL;
	return redirs;
}

//es
void	consume_redirs(t_list *redirs)
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
				temp_fd = creat(r->val, (unsigned int)00664);
			else if (r->type == REDIRLEFT)
				temp_fd = access(r->val, R_OK);
			else if (r->type == HEREDOC || r->type == PIPE_IN || r->type == PIPE_OUT)
				temp_fd = ft_atoi(r->val);

			if (temp_fd == -1) xit();
			if (close(temp_fd) == -1) xit();
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
			int	to, from;
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
			
			if (to == -1) xit();
			if (dup2(to, from) == -1) xit();
			if (close(to) == -1) xit();
		}
		r = get_redir(redirs, redir_i++);
	}
}

//es - pll exit??
extern char **environ;
void	execute_command(char	**argv, t_list *lst_redir, pid_t parent_pid, t_free to_free, t_parenthesis parenthesis)
{
	if (DEBUG_INIT) {
	printf("(%s) [%s%d%s] -- spawned from %s%d%s\n", argv[0], BLUE, getpid(), RESET, GREEN, parent_pid, RESET);}
	if (DEBUG_ARGV) {
	printf("(%s) [%s%d%s] -- args ", argv[0], BLUE, getpid(), RESET);
	print_argv(argv);}
	if (DEBUG_REDIR) {
	printf("(%s) [%s%d%s] -- redir ", argv[0], BLUE, getpid(), RESET);
	print_redirs(lst_redir->next); }
	
	consume_redirs(lst_redir->next);
	
	close_all_pipes(to_free.redirs, lst_redir);
	if (DEBUG_REDIR) {
	print_open_fds(10, STDERR_FILENO);}
	

	int		argc = arg_count(argv);
	char	**my_argv = ft_calloc(argc + 1, sizeof(char *));//nc
	int	i = 0;
	while (i < argc)
	{
		my_argv[i] = ft_strdup(argv[i]);//nc
		char *temp = handle_env(my_argv[i]);//nc
		FREE(my_argv[i]);
		my_argv[i] = temp;
		i++;
	}
	my_argv[i] = NULL;

	for(int x=0; x<to_free.p_count; x++) ft_lstclear(&(to_free.redirs)[x], &free_t_redir);
	frees2(1, 1, to_free.argvs);

	if (parenthesis.type == PARENTHESIS)
	{
		t_ast_node pll = (t_ast_node){PIPELINELIST, NULL, parenthesis.children};
		int status = execute_pll(&pll);
		garbage_collector(FREE_ALL, 0);
		exit(status);
	}
	else
	{
		if (is_builtin(my_argv[0]))
			exec_builtin(my_argv[0], my_argv, environ);
		else
		{
			char *pathname = ft_getpath(my_argv[0], environ); //nc
			execve(pathname, my_argv, environ);
			dprintf(2, "ms_turtle: command not found: %s\n", my_argv[0]);
			exit(14);
		}
	}
}

//es
pid_t	*init_subshells(char ***argvs, t_list **redirs, t_parenthesis *parens, int p_count)
{
	t_free	to_free = (t_free){argvs, redirs, p_count};
	pid_t	*pids = ft_calloc(p_count + 1, sizeof(pid_t)); //nc
	pid_t	parent = getpid();
	int	i = 0;
	(void) parens;

	while (i < p_count)
	{
		pids[i] = fork();
		if (pids[i] == -1) xit();
		if (pids[i] == 0)
			execute_command(argvs[i], redirs[i], parent, to_free, parens[i]);
		i++;
	}
	return pids;
}

#include <sys/wait.h>
//es
int	ms_execute(t_ast_node *pipeline)
{
	int arg_i = 0;
	int	pipe_i = 0;
	int	child_i = 0;
	int	p_count = count_child_pipes(pipeline) + 1;

	t_ast_node	*child = get_child(pipeline, child_i++); //nc
	char	***argvs = alloc_argvs(pipeline, p_count); //nc
	t_list	**redirs = init_redirs(p_count); //nc //[] of t_list heads
	t_parenthesis *parens = ft_calloc(p_count + 1, sizeof(t_parenthesis)); //nc
	int	_pipe[2] = {-1, -1};

	while (child != NULL)
	{	
		if (IS_LITERAL(child->type))
		{ (argvs[pipe_i])[arg_i++] = ft_strdup(child->content); }//nc
		else if (IS_REDIR(child->type))
		{
			t_list	*redir = alloc_redir(child->type, ft_strdup(child->content)); //nc
			ft_lstadd_back(&redirs[pipe_i], redir);
		}
		else if (child->type == HEREDOC)
		{
			int	fd_pipe_end = heredoc_handler(child->content);
			t_list	*redir = alloc_redir(HEREDOC, ft_itoa(fd_pipe_end)); //nc
			ft_lstadd_back(&redirs[pipe_i], redir);
		}
		else if (child->type == PIPE)
		{ 
			if (pipe(_pipe) == -1) xit();
			ft_lstadd_back(&redirs[pipe_i], alloc_redir(PIPE_OUT, ft_itoa(_pipe[1]))); //nc
			pipe_i++; arg_i = 0; parens[pipe_i] = (t_parenthesis){NONE, NULL};
			ft_lstadd_back(&redirs[pipe_i], alloc_redir(PIPE_IN, ft_itoa(_pipe[0]))); //nc
		}
		else if (child->type == PIPELINELIST)
		{ parens[pipe_i] = (t_parenthesis){PARENTHESIS, child->children}; 
		child->children = NULL;} //double free?
		else printf("ms_execute: BIG ERROR\n");
		
		child = get_child(pipeline, child_i++); //nc
	}

	//all argvs, redirs (left, right, append, heredocs, pipes) are ready
	pid_t	*pids = init_subshells(argvs, redirs, parens, p_count);
	
	close_all_pipes(redirs, NULL);

	int status = -42;
	for(int x=0; x<p_count; x++)
		waitpid(pids[x], &status, 0); //-1? i think we don care
	for(int x=0; x<p_count; x++) ft_lstclear(&redirs[x], &free_t_redir);
	frees2(2, 1, argvs, 0, pids);

	return status;
}

int	execute_pll(t_ast_node *pll)
{
	int	child_i = 0;
	t_ast_node *child = get_child(pll, child_i++); //nc?
	
	int status = 1;
	while (child != NULL)
	{
		if (status == 1)
		{
			if (child->type == PIPELINE)
				status = ms_execute(child);
			else if (child->type == PIPELINELIST)
				status = execute_pll(child);
		}
		else
			status = -42;
		t_ast_node *next = get_child(pll, child_i++); //nc?
		if (next == NULL) break;

		if (next->type == AND)
			status = (status == 0);
		if (next->type == OR)
			status = (status != 0);
		child = get_child(pll, child_i++); //nc?
	}
	return status;
}
