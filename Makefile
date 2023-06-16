NAME					:= minishell

UNAME_S					:= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  LINUX_INCLUDES		:= -I/usr/include
  OS_FLAG				:= -D LINUX
else
  LINUX_INCLUDES		:=
  OS_FLAG				:= -D OSX
endif

ifdef address
	FSANADDRESS			:= -fsanitize=address
else
	FSANADDRESS			:=
endif

ifdef leak
	FSANITIZELEAK		:= -fsanitize=leak
else
	FSANITIZELEAK		:=
endif

ifndef fsanitizeoff
	FSANITIZE			:= -fno-omit-frame-pointer -fstack-protector-all $(FSANADDRESS) $(FSANITIZELEAK)
else
	FSANITIZE			:=
endif

ifdef DEBUG
	DEVFLAGS			:= -ggdb $(FSANITIZE) -Wno-unused-function
	OPTFLAG				:= -O0
else
	DEVFLAGS			:=
	OPTFLAG				:= -O3
endif

CC						:= cc
CFLAGS					:= -Wall -Wextra -Werror -pedantic $(OPTFLAG) $(DEVFLAGS) $(OS_FLAG)
RM						:= rm -f

LIB_DIRECTORY			:= ./librairies/

LIBFT					:= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY			:= $(LIB_DIRECTORY)libft/
LIBFT_HEADERS			:= $(LIBFT_DIRECTORY)includes/

LIBPRINTF				:= $(LIBPRINTF_DIRECTORY)libftprintf.a
LIBPRINTF_DIRECTORY		:= $(LIB_DIRECTORY)ft_printf/
LIBPRINTF_HEADERS		:= $(LIBPRINTF_DIRECTORY)includes/

INCLUDE_DIR				:= ./includes/

# lm: default math lib
LIBRARIES				:= -lreadline -lftprintf -lft -L. -L$(LIBFT_DIRECTORY) -L$(LIBPRINTF_DIRECTORY) $(FRAMEWORK) $(LINUX_LIBS)
INCLUDES				:= -I$(LIBFT_HEADERS) -I$(LIBPRINTF_HEADERS) -I$(INCLUDE_DIR) $(LINUX_INCLUDES)

SOURCES_DIRECTORY		:= ./sources/
SOURCES_LIST			:= main.c\
							helpers.c\
							replace_envvar.c\
							lexer_helper.c\
							wildcard.c\
							print_lexeme_tlist.c\
							ast.c\
							print_ast.c\
							free_lexemes.c\
							execution.c\
							env_handler.c\
							builtins1.c\
							free_helpers.c

HEADER_LIST				:= ms.h
HEADER_FILES			:= $(addprefix $(INCLUDE_DIR), $(HEADER_LIST))

OBJECTS_DIRECTORY		:= objects/
OBJECTS_LIST			:= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS					:= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

#Unit Testing
TEST_DIR = ./tests/
SOURCES_TEST = $(subst main,,$(SOURCES_LIST))
OBJECTS_TEST = $(foreach wrd,$(SOURCES_TEST), $(OBJECTS_DIR)$(wrd).o)

.PHONY: all clean fclean re

all: $(NAME)

bonus: all

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "$(NAME): Creating $(LIBFT)..."
	@$(MAKE) -sC $(LIBFT_DIRECTORY) DEBUG=$(DEBUG)

$(LIBPRINTF):
	@echo "$(NAME): Creating $(LIBPRINTF)..."
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) DEBUG=$(DEBUG)

$(NAME): $(LIBFT) $(LIBPRINTF) $(OBJECTS_DIRECTORY) $(OBJECTS) $(HEADER_FILES)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBRARIES) $(INCLUDES) -o $(NAME)


clean:
	$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJECTS_DIRECTORY)
	rm -rf *.dSYM


clean_pipex:
	rm -rf $(OBJECTS_DIRECTORY)
	rm -rf *.dSYM


fclean: clean
	$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	$(MAKE) -sC $(LIBPRINTF_DIRECTORY) fclean
	rm -f $(NAME)


re: fclean all

norm:
	norminette includes/ sources/ libs/libft/ libs/libprintf/

funcs: $(NAME)
	@echo "Functions used in $(NAME):"
	nm -u $(NAME)

francinette_lft:
	cd libs/libft && cp includes/libft.h .
	cd libs/libft && ~/francinette/tester.sh
	cd libs/libft && rm libft.h
