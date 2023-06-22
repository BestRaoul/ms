
#ifndef MS_GLOBAL_G
# define MS_GLOBAL_G
typedef struct s_global {
	char	**env;
	int		status;
	int		dup_stdin;
	int		dup_stdout;
	int		print_ast;
} t_global;

extern t_global	g;
#endif

#ifndef MS_H
# define MS_H

# define IS_SPACE " \n\t\r\v\f"
# define SHELL_MSG "ms: "

# include "libft.h"
# include "colors.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>

typedef struct s_ast_node {
	int		type;
	char	*content;
	t_list	*children;
	int		node_is_cmd;
} t_ast_node;

//helpers.c
int		count(char c, char *str);
char	*chop(char *str, int end);
char	*_scan(char *str, int (*f)(char));
char	*_scan_nt(char *str, int (*f)(char));
char	*_scan2(char **str_ptr, int (*f)(char));
char	*join(char **strr, char *joint);

//gc helpers in helpers.c
int		strarr_count(char **strarr);
char	**realloc_strarr_no_gc(char **strarr);

//replace_envvar.c
int		is_aznum(char c);
char	*handle_dd(void);
char	*handle_status(void);
char	*handle_var(char *envvar);

/* stub function replacing $vars with their values */
char	*handle_env(char *s);
char	*handle_env_until(char *str, int end);

//wildcard.c
/* stub function returning files matching wildcard */
char	*handle_wildcard(char *s);
char	**wildmatches(char *token, char *cwd);
int		match(char *str, char *pattern);
void	add_wildmatches(t_list **lst, char *pattern);

/* lexing */
t_list	*lex(char *s);
//print_lex.c
void	print_lex(t_list *lst);
void	print_lex2(t_list *lst);

//lexer_helper.c
int find_literal_end(char *s);
char *list_2_str(t_list *lst);
char	**list_2_strr(t_list *lst);

//unwraping
t_list  *unwrap(t_list *lexemes);

/* parsing rewrite */
t_ast_node	*parse(t_list *lexemes);

//print_ast.c
void	print_ast(t_ast_node *ast, int depth);
void	print_type(int type);

/* execution */
int		execute(t_ast_node *pipeline_list);
int		execute_pipeline(t_ast_node *pipeline);

/* error management */
void	xit();
void	xit2(int err);

/* env */
void	print_env();
int		add_var_to_env(char *key, char *value);
int		remove_var_from_env(char *key);
int		find_in_env(char *key);

void	print_tlst(t_list *iter);
//unused
//int		replace_env_ast(t_ast_node *ast, t_ast_node *prev, int iscommand);

/* builtins */
int		is_builtin(char *cmd);
int		exec_builtin(char *cmd, char **argv);
int		cd(char **argv);
int		echo(char **argv);
int		export(char **argv);
int		unset(char **argv);
int		pwd_builtin();
int		env_builtin();
void	exit_builtin(char **argv);

enum TokenTypes {
	LPAREN,
	RPAREN,
	PIPE,
	REDIRLEFT,
	REDIRRIGHT,
	EQUAL,
	HEREDOCOP,
	APPEND,
	AND,
	OR,
	LITERAL,
	LITERAL_NQ,
	LITERAL_SQ,
	LITERAL_DQ,
	FAILED,
	END,
	//ARG

	NONE,
	PIPELINELIST,
	CMDLINE,
	CMDLINE_,
	GROUPING,
	PIPELINE,
	PIPELINE_SUFFIX,
	CMD,
	CMD_,
	REDIR,
	REDIROP,
	HEREDOC,
	//for consumption
	PIPE_IN,
	PIPE_OUT,
	PARENTHESIS,
};

t_ast_node	*init_ast_node_type(int type);

//helper
int	insert_token_into_lst(enum TokenTypes type, char *value, t_list **lst, int i);

/* parsing funcs */
int		prs_ast(t_list *lexemes, t_ast_node *ast);
int		prs_pipelinelist (int i, t_list *lexemes, t_ast_node *ast, int init);
int		prs_pipeline(int i, t_list *lexemes, t_ast_node *ast, int continued);
int		ast_mark_cmd(t_ast_node *ast, int is_first);


void	free_ast(t_ast_node *ast);


/* v1
	Cmdline ::= PipelineList
	PipelineList ::= Pipeline PipelineList?
	Pipeline ::= CmdInfix? PipeSuffix? | "("Pipeline")" PipeSuffix?
	PipeSuffix ::= '|' Pipeline | '&&' Pipeline | '||' Pipeline
	CmdInfix ::= CmdArg CmdInfix? | Redir CmdInfix? | Heredoc CmdInfix?
	Redir ::= RedirOp CmdArg
 	RedirOp ::= ">" | "<" | ">>"
	Heredoc ::= "<<" Lit
	CmdArg ::= Lit
 * */

/* v2
	Cmdline ::= PipelineList
	PipelineList ::= Pipeline PipelineList?
	Pipeline ::= CmdInfix? PipeSuffix? | "("Pipeline")" PipeSuffix?
	PipeSuffix ::= '|' Pipeline | '&&' Pipeline | '||' Pipeline | Redir PipeSuffix
	CmdInfix ::= CmdArg CmdInfix? | Redir CmdInfix? | Heredoc CmdInfix?
	Redir ::= RedirOp CmdArg
 	RedirOp ::= ">" | "<" | ">>"
	Heredoc ::= "<<" Lit
	CmdArg ::= Lit
 * */

#endif
