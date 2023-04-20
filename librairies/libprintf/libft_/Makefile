NAME		:= libft_.a
SRCS		:= ft_isdigit.c ft_strlen.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_bzero.c ft_memset.c ft_atoi.c
OBJS		:= ${SRCS:.c=.o}

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
RM			:= rm -f

LIBC		:= ar rc
LIBR		:= ranlib

.PHONY: all
all: ${NAME}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}
	${LIBR} ${NAME}

.PHONY: clean
clean:
	${RM} ${OBJS}

.PHONY: fclean
fclean: clean
	${RM} ${NAME}

.PHONY: re
re: fclean all