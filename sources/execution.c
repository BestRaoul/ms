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

/* TODO
 - pids
	- start -> sleep -> add pid to pids
 . redirs
	- add_redir L R HERE APP
	. consume
 . returns - RETHINK
	- waitpid for
	. -1
 . fix env (static for now)
*/

#define IS_LITERAL(x) (x == LITERAL_NQ || x == LITERAL_SQ || x == LITERAL_DQ)
#define IS_REDIR(x) (x == REDIRLEFT || x == REDIRRIGHT || x == APPEND)

typedef struct s_redir {
	int		type;
	char	*val;
} t_redir;

// https://tldp.org/LDP/abs/html/io-redirection.html

void	free_t_redir(void *ptr)
{
	if (ptr == NULL) return;
	if (((t_redir *)ptr)->val != NULL)
		free(((t_redir *)ptr)->val);
	free(ptr);
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

char	***alloc_argvs(t_ast_node *ast, int p_count)
{
	int	i = 0;
	int	j = 0;
	t_ast_node	*child = get_child(ast, i++);
//	printf("argv's: %d\n", count_child_pipes(ast) + 1);
	char ***argvs = calloc(p_count + 1, sizeof(char **)); //nc
	int literal_c = 0;
	while (child != NULL)
	{
		literal_c += (IS_LITERAL(child->type));
		if (child->type == PIPE)
		{
//			printf("(%d)-th argv: %d\n", j, literal_c + 1);
			argvs[j++] = calloc(literal_c + 1, sizeof(char *)); //nc
			literal_c = 0;
		}
		child = get_child(ast, i++);
	}
//	printf("(%d)-th argv: %d\n", j, literal_c + 1);
	argvs[j++] = calloc(literal_c + 1, sizeof(char *));
	argvs[j] = NULL;
	return (argvs);
}

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

void	print_argv(char **argv)
{
	int	arg_i = 0;
	printf("[%s", RED);
	while (argv[arg_i] != NULL)	printf("%s, ", argv[arg_i++]);
	printf("\b\b%s]\n", RESET);
}

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

	//second pass to just create the files unused
	redir_i = 0;
	r = get_redir(redirs, redir_i++);
	while (r != NULL)
	{
		if (redir_i != in_i && redir_i != out_i)
		{
			int temp_fd = -1;
			if (r->type == REDIRRIGHT || r->type == APPEND)
				temp_fd = creat(r->val, (unsigned int)00664);
			if (r->type == REDIRLEFT)
				;//check existence -1 => crash NO_SUCH_FILE_OR_DIRECTORY
			if (r->type == HEREDOC || r->type == PIPE_IN || r->type == PIPE_OUT)
				temp_fd = ft_atoi(r->val);
			if (temp_fd != -1)
				close(temp_fd);
			//if temp_fd && !REDIRLEFT
				//return errno
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
			if (r->type == HEREDOC || r->type == PIPE_IN)
			{ to = ft_atoi(r->val); from = STDIN_FILENO;}
			if (r->type == PIPE_OUT)
			{ to = ft_atoi(r->val); from = STDOUT_FILENO;}
			if (to == -1)
				printf("redir error: %s\n", strerror(errno));
			//if to = -1;
			//return -1, errno is already set
			dup2(to, from); //-1
			close(to);
		}
		r = get_redir(redirs, redir_i++);
	}
}

extern char **environ;
void	execute_command(char	**argv, t_list *lst_redir, pid_t parent_pid)
{
	printf("(%s) [%s%d%s] -- spawned from %s%d%s\n", argv[0], BLUE, getpid(), RESET, GREEN, parent_pid, RESET);
	printf("(%s) [%s%d%s] -- args ", argv[0], BLUE, getpid(), RESET);
	print_argv(argv);
	printf("(%s) [%s%d%s] -- redir ", argv[0], BLUE, getpid(), RESET);
	print_redirs(lst_redir->next);
	consume_redirs(lst_redir->next); //-1
	
	//getproperpath
	//execve("", argv, environ);

	//free_all();
	exit(0);
}

pid_t	*init_subshells(char ***argvs, t_list **redirs, int p_count)
{
	pid_t	*pids = calloc(p_count + 1, sizeof(pid_t)); //nc
	pid_t	parent = getpid();
	int	i = 0;

	while (i < p_count)
	{
		pids[i] = fork(); //error -1
		if (pids[i] == 0)
			execute_command(argvs[i], redirs[i], parent);
		i++;
	}
	return pids;
}

t_list	**init_redirs(int p_count)
{
	t_list **redirs = calloc(p_count, sizeof(t_list *)); //nc
	int	i = 0;

	while (i < p_count)
	{
		redirs[i] = ft_lstnew(NULL); //nc
		i++;
	}
	return redirs;
}

t_list	*alloc_redir(int type, char *val)
{
	if (val == NULL)
		return NULL;
	t_redir *redir = malloc(sizeof(t_redir)); //nc
	redir->type = type;
	redir->val = val;
	t_list *_redir = ft_lstnew(redir); //nc =>free
	return _redir;
}

int	heredoc_handler(char *delimiter)
{
	int	_pipe[2];
	pipe(_pipe); //-1
	char	*input;

	input = readline("|> ");
	while (strcmp(input, delimiter) != 0)
	{
		write(_pipe[1], input, ft_strlen(input));
		input = readline("|> ");
	}
	close(_pipe[1]);
	return _pipe[0];
}

#include <sys/wait.h>
void	ms_execute(t_ast_node *pipeline)
{
	int arg_i = 0;
	int	pipe_i = 0;
	int	child_i = 0;
	int	p_count = count_child_pipes(pipeline) + 1;

	t_ast_node	*child = get_child(pipeline, child_i++); //nc
	char	***argvs = alloc_argvs(pipeline, p_count); //nc
	t_list	**redirs = init_redirs(p_count); //nc //array of t_list_ptr
	int	_pipe[2] = {-1, -1};

	while (child != NULL)
	{
		/* --plan--
		//LITERAL -done
		//REDIR	  -done
		//PIPE	  -done
		//PIPELINE
			//-r ms_exec
			//return value management
		//AND,OR ??
			//'&&'/'||' found = inside parenthesis
		*/
		
		if (IS_LITERAL(child->type))// && !IS_REDIR(prev_type))
			(argvs[pipe_i])[arg_i++] = ft_strdup(child->content); //nc
		else if (IS_REDIR(child->type))
		{
			t_list	*redir = alloc_redir(child->type, ft_strdup(child->content)); //nc
			ft_lstadd_back(&redirs[pipe_i], redir);
		}
		else if (child->type == HEREDOC)
		{
			int	fd_pipe_end = heredoc_handler(child->content);
			ft_lstadd_back(&redirs[pipe_i], alloc_redir(HEREDOC, ft_itoa(fd_pipe_end))); //nc
		}
		else if (child->type == PIPE)
		{ 
			pipe(_pipe); //-1
			ft_lstadd_back(&redirs[pipe_i], alloc_redir(PIPE_OUT, ft_itoa(_pipe[1]))); //nc
			pipe_i++; arg_i = 0;
			ft_lstadd_back(&redirs[pipe_i], alloc_redir(PIPE_IN, ft_itoa(_pipe[0]))); //nc
		}
		else if (child->type == PIPELINE)
			ms_execute(child); // (if fail =>return -1;)
		else //&& or ||
			printf("BIG ERROR");
		
		child = get_child(pipeline, child_i++); //nc
	}
	//all redirs are ready
	//all argvs are ready
	//all heredoc pipes, ready.
	pid_t	*pids = init_subshells(argvs, redirs, p_count); //error check -1
	(void) pids;
	
	//return value management
	for(int x=0; x<p_count; x++) waitpid(pids[x], NULL, 0);
	for(int x=0; x<p_count; x++) ft_lstclear(&redirs[x], &free_t_redir);
	frees2(2, 1, argvs, 0, pids);
}

void	execute_pl(t_ast_node *pl)
{
	t_ast_node *first_child = get_child(pl, 0);
	ms_execute(first_child);
	/* --logic--
	succes = 1;
	for each (child)
	{
		succes = exec child
		if (!next) break;
		if (succes)
			AND |> exec next
			OR |> exec next+1
		else (!succes)
			AND |> break
			OR	|> exec next
	}
	printf(succes ? GREEN : RED);
	*/
}

//int	execve(path, argv, env);
/* fork => execve example
int	launch_sub(char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		return execve(argv[0], argv, NULL);
	else
		return 0;
}
*/

/* all token types you can find in a proper ast execute-ready tree
PIPE, // new argv
REDIRLEFT, // redirect
REDIRRIGHT, //redirect
HEREDOCOP, //redirect (but weirder, use static string for testing)
APPEND, >> //redirect but different
AND, //after of pipeline
OR, //after pipeline
LITERAL_NQ, //arg
LITERAL_SQ, //arg
LITERAL_DQ, //arg
PIPELINELIST,
PIPELINE, //inside
*/


