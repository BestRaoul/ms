LIBFT_NAMES	= isalpha isdigit isalnum isascii isprint strlen memset bzero memcpy memmove strlcpy strlcat toupper tolower strchr strrchr strncmp memchr memcmp strnstr atoi calloc strdup substr strjoin strtrim split itoa strmapi striteri putchar_fd putstr_fd putendl_fd putnbr_fd lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear lstiter lstmap

FT_PRINTF_NAMES	= ft_printf ft_other_printf ft_get_flags ft_get_flags_helpers ft_helpers ft_helpers2 get_char get_str get_int get_uint get_ptr get_hex

CUSTOM_NAMES	= ft_intr frees ft_atod free_arr ft_size comparison

LIB_SRCS	+= $(foreach wrd,$(LIBFT_NAMES), ft_$(wrd).c) 
LIB_SRCS	+= $(foreach wrd,$(FT_PRINTF_NAMES), ft_printf/$(wrd).c) 
LIB_SRCS	+= $(foreach wrd,$(CUSTOM_NAMES), $(wrd).c) 

LIB_OBJS	= ${LIB_SRCS:.c=.o}

NAME	= libft.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -I.

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${LIB_OBJS} 
			@ar -rcs ${NAME} ${LIB_OBJS}

all:		${NAME}

clean:
			@${RM} ${LIB_OBJS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
