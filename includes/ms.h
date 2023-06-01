
#ifndef MS_H
# define MS_H

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

// lexing
t_list	*scan_tokens(char *s);

//wildcards
char	**wildmatches(char *token, char *cwd);

//replace_envvar.c
int		in(char c, char *str);
int		is_azAZ09_(char c);
void	replace_envvars(t_list *lexemes);

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
	EPSILON,
};

/*enum NonTerminals {

};*/

enum SymbolType {
	TERMINAL,
	NONTERMINAL
};

enum AstType {
	COMMAND
};



typedef struct s_symbol
{
	enum SymbolType		terminality_type;
	int					type;
}	t_symbol;

typedef struct s_rule {
	int			name;
	int 		*symbols;
	int			num_symbols;
	int			terminality;
} t_rule;

typedef struct s_grammar {
	t_rule*	rules;
	int		num_rules;
} t_grammar;

typedef struct s_ast_node {
	int		type;
	char	*content;
	t_list	*children;
} t_ast_node;


t_ast_node	*init_ast_node_type(int type);

/* parsing funcs */
int	prs_pipelinelist (int i, t_list *lexemes, t_ast_node *ast);
int	prs_pipeline(int i, t_list *lexemes, t_ast_node *ast, int continued);

void	print_ast(t_ast_node *ast, int depth);
void	print_type(int type);

/*
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

/* last version, might be flawed
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


//CMDLINE -> CMDLINE' AND CMDLINE
//CMDLINE -> CMDLINE' OR CMDLINE
//CMDLINE' -> CMDLINE | epsilon

/* https://www.tutorialspoint.com/compiler_design/compiler_design_syntax_analysis.htm */
/*const t_grammar grammar = {
		(t_rule[]) {
				{CMDLINE, (int[]){PIPELINE}, 1, NONTERMINAL},
				{CMDLINE, (int[]){GROUPING}, 1, NONTERMINAL},
				{CMDLINE, (int[]){CMDLINE_, AND, CMDLINE}, 3, NONTERMINAL},
				{CMDLINE, (int[]){CMDLINE_, OR, CMDLINE}, 3, NONTERMINAL},
				{CMDLINE_, (int[]){CMDLINE, EPSILON}},
				{GROUPING, (int[]){LPAREN, CMDLINE, RPAREN}, 3, NONTERMINAL},

				{PIPELINE, (int[]){CMD, PIPE, PIPELINE_SUFFIX}, 1, NONTERMINAL},
				{PIPELINE_SUFFIX, (int[]){CMD, PIPE, PIPELINE_SUFFIX}, 3, NONTERMINAL},
				{PIPELINE_SUFFIX, (int[]){CMD}, 1, NONTERMINAL},

				{CMD, (int[]){LITERAL}, 1, NONTERMINAL},
				{CMD, (int[]){REDIR}, 1, NONTERMINAL},
				{CMD, (int[]){CMD, LITERAL}, 2, NONTERMINAL},
				{CMD, (int[]){CMD, REDIR}, 2, NONTERMINAL},
				{REDIR, (int[]){REDIROP, LITERAL}, 2, NONTERMINAL},
				{REDIROP, (int[]){REDIRLEFT}, 1, TERMINAL},
				{REDIROP, (int[]){REDIRRIGHT}, 1, TERMINAL},
				{REDIROP, (int[]){APPEND}, 1, TERMINAL},
				{HEREDOC, (int[]){HEREDOCOP, LITERAL}, 2, TERMINAL},
		},
		18
};*/

/* OLD
	Cmdline ::= PipelineList
	PipelineList ::= Pipeline PipelineList?
	Pipeline ::= Cmd PipeSuffix? | Redir PipeSuffix? | Heredoc PipeSuffix? | "("Pipeline")" PipeSuffix?
	PipeSuffix ::= '|' Pipeline | '&&' Pipeline | '||' Pipeline
	Cmd ::= Lit CmdSuffix?
	CmdSuffix ::= Lit
	Redir ::= RedirOp Lit
	RedirOp ::= ">" | "<" | ">>"
	Heredoc ::= "<<" Lit
 * */

#endif
