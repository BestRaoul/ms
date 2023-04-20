/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:11:34 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/31 12:13:10 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft_/libft_.h"

typedef struct s_format
{
	int			flags[5];
	size_t		width;
	size_t		precision;
	char		conversion;
	int			has_precision;
	int			chars_printed;
}	t_format;

void			print_format(t_format *t);
int				ft_printf(const char *format_str, ...);
int				cab_(const char *str, char c);
int				str_contains_flag(char *str, t_format *t);
void			get_flags(t_format *t, char **str);
int				get_width(t_format *t, char **str);
int				get_precision(t_format *t, char **str);
void			get_conversion(t_format *t, char **str);
t_format		*build_format(char **str);
void			print_blanks(size_t amount, t_format *t);
void			print_zeroes(size_t amount, t_format *t);
void			put_str_len(const char *str, size_t len, t_format *t);
void			put_hex_fd(size_t n, int capitalize, int prefix, int fd);
void			put_size_t_fd(size_t n, int fd);

void			print_char(t_format *t, char c);
void			print_str(t_format *t, char *str);
void			print_void_ptr(t_format *t, void *ptr);
void			print_int(t_format *t, int n);
void			print_unsigned(t_format *t, size_t n);
void			print_hexadecimal(t_format *t, size_t n);
void			print_percent(t_format *t);

int				clamp_int(int min, int max, int val);
size_t			clamp_size_t(size_t min, size_t max, size_t val);
size_t			ft_max(size_t a, size_t b);
size_t			ft_min_(size_t a, size_t b);
int				int_max(int a, int b);
int				ft_pow(int a, int b);
size_t			size_t_pow(size_t a, size_t b);
void			ft_put_size_t(size_t n, t_format *t);
size_t			unsigned_num_width_size_t(size_t n, int base);
size_t			signed_width_size_t(int n, int base);
int				my_abs(int a);
void			count_put_char(char c, t_format *t);
void			count_put_str(char *str, t_format *t);

size_t			hex_width(t_format *t, unsigned int n);
void			handle_no_width(t_format *t, size_t n, size_t prec_len);

#endif
