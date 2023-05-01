
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
int		findf(int (*f)(char), char *str);
int		findf_nt(int (*f)(char), char *str);
int		len(char *str);
int		count(char c, char *str);
char	*chop(char *str, int end);
char	*_scan(char *str, int (*f)(char));
char	*join(char **strr, char *joint);
void	print_lexeme_tlist(t_list *lst);

// lexing
t_list	*scan_tokens(char *s);

//wildcards
char	**wildmatches(char *token, char *cwd);

//replace_envvar.c
int	in(char c, char *str);
int	is_azAZ09_(char c);
void	replace_env_variables(char *input, char **input_ptr);

/* stub function replacing $vars with their values */
char	*handle_env(char *s);

/* stub function returning files matching wildcard */
char	*handle_wildcard(char *s);

// TODO: mor literal types telling if they can be substituted or not
enum TokenTypes {
	LPAREN = 0,
	RPAREN = 1,
	PIPE = 2,
	REDIRLEFT = 3,
	REDIRRIGHT = 4,
	EQUAL = 5,
	HEREDOC = 6,
	APPEND = 7,
	AND = 8,
	OR = 9,
	LITERAL_NQ = 10,
	LITERAL_SQ = 11,
	LITERAL_DQ = 12,
	//ARG = 10
};
#endif
