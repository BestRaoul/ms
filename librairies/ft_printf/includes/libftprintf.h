/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:51:22 by pkondrac          #+#    #+#             */
/*   Updated: 2022/11/21 21:15:46 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_pfpd {
	char	specifier;
	char	flags;
	int		width;
	int		precision;
}	t_pfpd;

//ft_printf.c
int		ft_printf(const char *format, ...);
char	*get_format(t_pfpd data, va_list va);
//ft_other_printf.c
char	*ft_allocprintf(const char *format, ...);
char	*ft_yoloprintf(char *str, const char *format, ...);
//ft_get_flags.c
t_pfpd	ft_get_flags(const char *format, va_list va);
//ft_get_flags_helpers.c
int		ft_is_flag(char c);
int		ft_is_specifier(char c);
//ft_helpers.c
char	*last(char *s);
int		ft_min(int x, int y);
int		ft_max(int x, int y);
//ft_helpers2.c
void	ft_append_num(char *str, long x, int width, char *base);
void	ft_append_ul(char *str, unsigned long x, int width, char *base);
int		long_size(long x, int div);
int		ulong_size(unsigned long x, int div);
//get_*.c
char	*get_char(t_pfpd data, va_list va);
char	*get_perc(t_pfpd data, va_list va);
char	*get_str(t_pfpd data, va_list va);
char	*get_int(t_pfpd data, va_list va);
char	*get_uint(t_pfpd data, va_list va);
char	*get_ptr(t_pfpd data, va_list va);
char	*get_hex(t_pfpd data, va_list va);
#endif
