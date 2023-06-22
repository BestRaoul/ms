/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 12:42:36 by jwikiera         ###   ########.fr       */
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

typedef struct s_global {
	char	**env;
	int		status;
	int		dup_stdin;
	int		dup_stdout;
	int		print_ast;
	t_list	**redirs;
}	t_global;

extern t_global	g_;

typedef t_dict_int_str_member	t_dism;

typedef struct s_ast_node {
	int		type;
	char	*content;
	t_list	*children;
}	t_ast_node;

enum TokenTypes {
	LPAREN,
	RPAREN,
	PIPE,
	REDIRLEFT,
	REDIRRIGHT,
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
int find_literal_end(char *s);
int	insert_token_into_lst(enum TokenTypes type, char *value, t_list **lst, int i);

//unwraping.c
t_list  *unwrap(t_list *lexemes);
//replace_envvar.c
char	*handle_env(char *s);
//replace_wildcard.c
void	add_wildmatches(t_list **lst, char *pattern);

//parsing.c
t_ast_node	*parse(t_list *lexemes);

/* execution */
void	execute(t_ast_node *pipeline_list);

/* error management */
void	crash(void);
void	close_and_free_all(void);

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
t_ast_node	*add_child(t_ast_node *parent, t_ast_node new);

#endif
