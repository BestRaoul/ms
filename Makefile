NAME	= ms

#Commands
CC		= gcc
RM		= rm -f
CFLAGS	= -g#-O3 #-Wall -Wextra -Werror 

#Variables
INCLUDE_DIR = ./includes/
LIBFT_DIR = ./librairies/libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_HEADERS = $(LIBFT_DIR)./

LIBRAIRIES = -lreadline -L. -L$(LIBFT_DIR) -lft
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

SOURCES_DIR = ./sources/
SOURCES_LIST = main replace_envvar helpers
SOURCES	= $(foreach wrd,$(SOURCES_LIST), $(SOURCES_DIR)$(wrd).c)

OBJECTS_DIR = ./objects/
OBJECTS	= $(foreach wrd,$(SOURCES_LIST), $(OBJECTS_DIR)$(wrd).o)

#Unit Testing
TEST_DIR = ./tests/
SOURCES_TEST = $(subst main,,$(SOURCES_LIST))
OBJECTS_TEST = $(foreach wrd,$(SOURCES_TEST), $(OBJECTS_DIR)$(wrd).o)

#Coolors
RESET = \033[0;39m
GREEN = \033[0;92m
RED = \033[0;91m
BLUE = \033[0;94m
BOLD = \033[0;1m

#makes
all:		${NAME}

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o : $(SOURCES_DIR)%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "$(NAME): Creating $(LIBFT)..."
	@$(MAKE) -sC $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJECTS_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBRAIRIES) $(INCLUDES) -o $(NAME)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJECTS_DIR)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean:		clean
	@$(MAKE) -sC $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(NAME): $(NAME) was deleted"

re: fclean all

$(OBJECTS_DIR)%.o : $(TEST_DIR)%.c
	@$(CC) $(CFLAGS) -c $(LIBRAIRIES) $(INCLUDES) $< -o $@

test: $(LIBFT) $(OBJECTS_DIR) $(OBJECTS_TEST) $(OBJECTS_DIR)unit_envvar.o
	@$(CC) $(CFLAGS) $(OBJECTS_DIR)unit_envvar.o $(OBJECTS_TEST) $(LIBRAIRIES) $(INCLUDES) -o $(TEST_DIR)temp
	@./$(TEST_DIR)temp
	@rm $(TEST_DIR)temp

.PHONY:		all clean fclean re bonus test
