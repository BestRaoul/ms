FT_PRINTF_NAMES	= ft_printf ft_other_printf ft_get_flags ft_get_flags_helpers ft_helpers ft_helpers2 get_char get_str get_int get_uint get_ptr get_hex ret

LIB_SRCS	= $(foreach wrd,$(FT_PRINTF_NAMES), ./$(wrd).c)

LIB_OBJS	= ${LIB_SRCS:.c=.o}

NAME	=	libftprintf.a

CC		= gcc

RM		= rm -f

ifdef DEBUG
	DEVFLAGS			:= -ggdb $(FSANITIZE) -Wno-unused-function
	OPTFLAG				:= -O0
else
	DEVFLAGS			:=
	OPTFLAG				:= -O3
endif

CFLAGS	= -Wall -Wextra -Werror -pedantic $(DEVFLAGS) $(OPTFLAG) -I. -I./includes -I../libft/includes

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
