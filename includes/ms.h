/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2023/06/29 15:48:24 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/types.h>
# include <signal.h>
# ifndef __ANDROID__
#  include <sys/termios.h>
# else
#  include <termios.h>
# endif
# include <termios.h>

# ifndef __ANDROID__
#  define ECHOCTL  	0x00000040
# endif

typedef struct s_global {
	char			**env;
	int				status;
	int				dup_stdin;
	int				dup_stdout;
	int				print_ast;
	t_list			**redirs;
	int				is_sig;
	struct termios	orig_termios;
}	t_global;

typedef struct s_ast_node {
	int		type;
	char	*content;
	t_list	*children;
}	t_ast_node;

typedef t_ast_node	t_an;

extern t_global		g_;

enum e_TokenTypes {
	LPAREN,
	RPAREN,
	PIPE,
	REDIR_L,
	REDIR_R,
	APPEND,
	AND,
	OR,
	HEREDOC,
	LITERAL,
	END,
	NONE,
	PIPELINELIST,
	PIPELINE,
	PIPE_IN,
	PIPE_OUT,
	PARENTHESIS,
};

// lexing.c
t_list	*lex(char *s);
//lex + unwrap.c
int		find_literal_end(char *s);
int		insert_token_into_lst(enum e_TokenTypes type, char *value,
			t_list **lst, int i);

//unwraping.c
t_list	*unwrap(t_list *lexemes);
void	unmark_ignored_stars(t_list *iter);
void	mark_ignored_stars(t_list *iter);

//replace_envvar.c
char	*handle_env(char *s);
int		export_valid(char *s);
//replace_wildcard.c
void	add_wildmatches(t_list **lst, char *pattern);

//parsing.c
t_an	*parse(t_list *lexemes);

/* execution */
void	execute(t_ast_node *pipeline_list);

/* builtins */
int		is_builtin(char *cmd);
int		exec_builtin(char *cmd, char **argv);
int		cd(char **argv);
int		echo(char **argv);
int		export(char **argv);
int		unset(char **argv);
int		pwd_builtin(void);
int		env_builtin(void);
void	exit_builtin(char **argv);

//wildcard_helpers.c
int		match(char *str, char *pattern);

/* env */
void	print_env(void);
int		add_var_to_env(char *key, char *value);
int		remove_var_from_env(char *key);
int		find_in_env(char *key);
char	*where_bin(char *binname);

//replace_envvar_helpers.c
int		is_aznum(char c);
char	*handle_dd(void);
char	*handle_status(void);
char	*handle_var(char *envvar);

//helpers.c
int		count(char c, char *str);
char	*chop(char *str, int end);
char	*_scan2(char **str_ptr, int (*f)(char));
char	*join(char **strr, char *joint);
void	next(t_list **i_ptr);

//gc helpers in helpers.c
int		strarr_count(char **strarr);
char	**realloc_strarr_no_gc(char **strarr);

//print_ast.c
void	print_ast(t_ast_node *ast, int depth);

/* sighandlers */
void	handler_c(int sig, siginfo_t *info, void *context);
void	handler_slash(int sig, siginfo_t *info, void *context);

//helpers --------------------------------------------

//lex_helpers.c
int		_type(t_list *lexeme);
char	*_content(t_list *lexeme);
char	**_content_ptr(t_list *lexeme);
char	*_type_str(t_list *lexme);
t_dism	*_member(t_list *lexeme);
//2.c

//unwrap_helpers.c
char	*list_2_str(t_list *lst);
char	**list_2_strr(t_list *lst);
char	**ft_splitf(char *s, int (*next)(char *));
int		add_until(t_list **strs_ptr, char *s);
int		add_string(t_list **lst, char *s);

//ast_helpers.c
int		parse_arg(t_list *lexeme, t_ast_node *ast);
int		parse_redir(t_list *lexeme, t_ast_node *ast);
int		parse_heredoc(t_list *lexeme, t_ast_node *ast);
int		parse_suffix(t_list *lexeme, t_ast_node *ast);
//2
int		is_redir(int t);
t_an	*add_child(t_ast_node *parent, t_ast_node new);

typedef struct s_redir {
	int		type;
	char	*val;
}	t_redir;

typedef struct s_parenthesis
{
	int		type;
	t_list	*children;
}	t_parenthesis;

//execute_helpers.c
# define DEBUG_INIT 0
# define DEBUG_REDIR 0
# define DEBUG_ARGV 0
//error managment -full
void	set_g_status(int err);
void	reown(char **strr);
void	close_all_pipes(t_list *ignore, int do_crash);
void	close_and_free_all(void);
void	crash(void);
//2
void	debug_prints_execute_command(char **argv, t_list *l_r, pid_t p_pid);
//3
t_an	*get_child(t_ast_node	*node, int i);
t_redir	*get_redir(t_list	*redir, int i);
t_list	*alloc_redir(int type, char *val);
char	***alloc_argvs(t_ast_node *ast, int pipe_count);
//4
int		consume_redirs(t_list *redirs);
//5
int		count_child_pipes(t_ast_node *ast);
int		heredoc_handler(char *delimiter);
void	populate_execution_data(char ***argvs,
			t_parenthesis *parens, t_ast_node *pipeline);

void	main_loop(void);
void	disown_pathname_and_free_all(char *pathname);

#endif
