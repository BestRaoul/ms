
#ifndef MS_H
# define MS_H

//#define _GNU_SOURCE             /* See feature_test_macros(7) */
//#include <fcntl.h>              /* Obtain O_* constant definitions */
//#include <unistd.h>

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>

# define RESET "\033[0m"
//COLORS - normal
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
//COLORS - bold
# define BBLACK "\033[1;30m"
# define BRED "\033[1;31m"
# define BGREEN "\033[1;32m"
# define BYELLOW "\033[1;33m"
# define BBLUE "\033[1;34m"
# define BPURPLE "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BWHITE "\033[1;37m"

//helpers.c
int		find(char c, char *str);
int		find_noescape(char c, char *str);
int		findf(int (*f)(char), char *str);
int		findf_nt(int (*f)(char), char *str);
int		len(char *str);
int		count(char c, char *str);
char	*chop(char *str, int end);
char	*_scan(char *str, int (*f)(char));
char	*_scan_nt(char *str, int (*f)(char));
char	*_scan2(char **str_ptr, int (*f)(char));
char	*join(char **strr, char *joint);
void	print_lexeme_tlist(t_list *lst);
void	print_lexeme_tlist2(t_list *lst);
void	free_lexeme_node(void *node);

// lexing
t_list	*scan_tokens(char *s);

//wildcards
char	**wildmatches(char *token, char *cwd);

//replace_envvar.c
int		in(char c, char *str);
int		is_azAZ09_(char c);

/* stub function replacing $vars with their values */
char	*handle_env(char *s);

/* stub function returning files matching wildcard */
char	*handle_wildcard(char *s);

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

typedef struct s_ast_node {
	int		type;
	char	*content;
	t_list	*children;
} t_ast_node;


t_ast_node	*init_ast_node_type(int type);

/* parsing funcs */
int		prs_ast(t_list *lexemes, t_ast_node *ast);
int		prs_pipelinelist (int i, t_list *lexemes, t_ast_node *ast, int init);
int		prs_pipeline(int i, t_list *lexemes, t_ast_node *ast, int continued);

void	print_ast(t_ast_node *ast, int depth);
void	print_type(int type);
void	free_ast(t_ast_node *ast);

/* parse rewrite */
t_ast_node	*parse_ast2(t_list *lexemes);

/* execution */
int		ms_execute(t_ast_node *pipeline);
int		execute_pll(t_ast_node *pl);

/* error management */
void	xit();
void	xit2(int err);

/* env */
char	**copy_env(char **env, char *excl);
void	print_env(char **env);
int		add_var_to_env(char *key, char *value, char ***env);
int		remove_var_from_env(char *key, char ***env);

int		replace_env_ast(t_ast_node *ast, t_ast_node *prev, int iscommand);

/* builtins */
int		cd(char *dir);

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
