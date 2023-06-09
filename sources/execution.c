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
	. add_redir L R HERE APP
	. consume
 . returns - RETHINK
	. waitpid for
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
	int	prev_type = LITERAL;
	while (child != NULL)
	{
		literal_c += (IS_LITERAL(child->type) && !IS_REDIR(prev_type));
		prev_type = child->type;
		if (child->type == PIPE)
		{
//			printf("(%d)-th argv: %d\n", j, literal_c + 1);
			argvs[j++] = calloc(literal_c + 1, sizeof(char *)); //nc
			literal_c = 0;
			prev_type = LITERAL;
		}
		child = get_child(ast, i++);
	}
//	printf("(%d)-th argv: %d\n", j, literal_c + 1);
	argvs[j++] = calloc(literal_c + 1, sizeof(char *));
	argvs[j] = NULL;
	return (argvs);
}

void	print_argv(char **argv)
{
	int	arg_i = 0;
	printf("[%s", RED);
	while (argv[arg_i] != NULL)	printf("%s, ", argv[arg_i++]);
	printf("\b\b%s]\n", RESET);
}

void	print_redir(t_list *redir)
{
	int	redir_i = 0;
	t_redir *r = get_redir(redir, redir_i++);
	printf("[%s", r ? "" : "  ");
	while (r != NULL)
	{
		printf("%s", BPURPLE);
		if (r->type == REDIRLEFT) printf("<");
		if (r->type == REDIRRIGHT) printf(">");
		if (r->type == APPEND) printf(">>");
		printf("%s%s%s%s, ", RESET, CYAN, r->val, RESET);
		r = get_redir(redir, redir_i++);
	}
	printf("\b\b%s]\n", RESET);
}

void	execute_command(char	**argv, t_list *lst_redir, pid_t parent_pid)
{
	printf("(%s) [%s%d%s] -- spawned from %s%d%s\n", argv[0], BLUE, getpid(), RESET, GREEN, parent_pid, RESET);
	printf("(%s) [%s%d%s] -- args ", argv[0], BLUE, getpid(), RESET);
	print_argv(argv);
	printf("(%s) [%s%d%s] -- redir ", argv[0], BLUE, getpid(), RESET);
	print_redir(lst_redir->next);
	exit(0); //->work here
	
	/*consume_redirs()
		//heredoc
			//pipe(start, end)
			//dup2(start, stdin);
			//close(start)
			//start_interactive readline_sessions + waiting for char
			//reset(stdin)
			//dup2(end, STDIN)
		//consume(file, STD*)
			//if !file: create()
			//pid = open(file, r/w, overwrite/append)
			//dup2(pid, dup(STD*))
		>'log_file': //dup2(log_file, dup(STDIN))
		<'in_file': //dup2(in_file, dup(STDOUT))
	*/
	//dup2(pipe[-1].end, STDIN)
	//dup2(pipe[0].start, STDOUT)
	
	//launch(argv[_i++]);
		/*
		pathname = find_in_getenv(PATH)
		env = our_env;
		argv;
		*/
	//spawn(argv)
		//fork();
			//PID=0
				//launch();
				//if -1: print("FAIL"); exit(1); send -1 to father;
			//else
				//continue; -> save PID next to argv in table
				//waiting for signal to know if it failed
}

pid_t	*init_subshells(char ***argvs, t_list **redirs, int p_count)
{
	pid_t	*pids = calloc(p_count + 1, sizeof(pid_t)); //nc
	pid_t parent = getpid();
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

#include <signal.h>
void	start_subshells(pid_t *pids, int p_count)
{
	int	i = 0;
	while (i < p_count)
	{
		kill(pids[i], SIGUSR1);
		i++;
	}	
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

	int	prev_type = NONE;
	while (child != NULL)
	{
		/* --plan--
		//LITERAL -done
		//REDIR
			//handle redir -> switch
		//PIPE
			//j=0; argvs++; redirect both out and in
		//PIPELINE
			//-r ms_exec
		//AND,OR ??
			//'&&'/'||' found = inside parenthesis
		*/
		
		
		if (IS_LITERAL(child->type) && !IS_REDIR(prev_type))
			(argvs[pipe_i])[arg_i++] = ft_strdup(child->content); //nc
		else if (IS_LITERAL(child->type)) ;
		else if (IS_REDIR(child->type))
		{
			t_ast_node *next_child = get_child(pipeline, child_i);
			t_redir *redir = calloc(1, sizeof(t_redir)); //nc
			if (next_child != NULL)
				redir->val = ft_strdup(next_child->content); //nc
			redir->type = child->type;
			ft_lstadd_back(&redirs[pipe_i], ft_lstnew(redir)); //nc
		}
		else if (child->type == HEREDOCOP) ;
		else if (child->type == PIPE)
		{ pipe_i++; arg_i = 0; prev_type = NONE;}
		else if (child->type == PIPELINE)
			ms_execute(child); // (if fail =>return -1;)
		else //&& or ||
			printf("BIG ERROR");
		
		if (child->type != PIPE) prev_type = child->type;
		child = get_child(pipeline, child_i++); //nc
	}
	//all redirs are ready
	//all argvs are ready
	//heredoc pipes, NOT-ready yet.
	print_argvs(argvs, p_count);
	pid_t	*pids = init_subshells(argvs, redirs, p_count); //error check -1
	(void) pids;
	//wait_pid_all
		//int	*returns[]; .. if last return -1 => paint it red!
	//pause();
	
	for(int x=0; x<p_count; x++) waitpid(pids[x], NULL, 0);
	for(int x=0; x<p_count; x++) ft_lstclear(&redirs[x], (void (*)(void *))free_ast);
	frees2(1, 1, argvs);
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


