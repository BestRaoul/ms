NAME		:= libftprintf.a
#SRCS		:= ft_printf.c conversion_helpers.c flag_helpers.c ft_t_format_builder.c precision_helpers.c print_char.c util.c width_helpers.c print_str.c math_util.c math_util2.c util2.c print_void_ptr.c put_hex_fd.c print_int.c util3.c print_unsigned.c put_size_t_fd.c print_hexadecimal.c
SRCS		= libft_/ft_putnbr_fd.c libft_/ft_bzero.c libft_/ft_memset.c libft_/ft_atoi.c\
              libft_/ft_isdigit.c              libft_/ft_putstr_fd.c \
              libft_/ft_calloc.c \
              libft_/ft_putchar_fd.c \
              libft_/ft_strlen.c \
              ft_printf.c conversion_helpers.c flag_helpers.c ft_t_format_builder.c precision_helpers.c print_char.c util.c width_helpers.c print_str.c math_util.c math_util2.c util2.c print_void_ptr.c put_hex_fd.c print_int.c util3.c print_unsigned.c put_size_t_fd.c print_hexadecimal.c print_hexadecimal_2.c print_percent.c
#$(wildcard *.c libft_/*.c)
OBJS		:= ${SRCS:.c=.o}
#LDFLAGS		:= -static -L./libft_ -lft

libft_		:= ./libft_/libft_.a

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -ggdb
RM			:= rm -f

LIBC		:= ar rc
LIBR		:= ranlib

.PHONY: all
all: ${NAME}

libft_.a:
	make all bonus -C libft_

#${NAME}: libft_.a ${OBJS}
#	${LIBC} ${NAME} ${OBJS} ${libft_}
#	${LIBR} ${NAME}

bonus: all
	echo "bonus :)"

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}
	${LIBR} ${NAME}

# .PHONY: bonus
# bonus: ${OBJS} ${OBJS_BONUS}
# 	${LIBC} ${NAME} ${OBJS} ${OBJS_BONUS}
# 	${LIBR} ${NAME}

.PHONY: clean
clean:
	${RM} ${OBJS}

.PHONY: fclean
fclean: clean
	${RM} ${libft_}
	${RM} ${NAME}

.PHONY: re
re: fclean all
