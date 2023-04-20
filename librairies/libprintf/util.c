/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:23:20 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/31 16:23:22 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	cab_(const char *str, char c)
{
	return (*str == c);
}

void	print_format(t_format *t)
{
	ft_putstr_fd_("t_format: \n", 1);
	ft_putstr_fd_("\tflags: ", 1);
	if (t->flags[0])
		ft_putstr_fd_("'-'", 1);
	if (t->flags[1])
		ft_putstr_fd_("'0'", 1);
	if (t->flags[2])
		ft_putstr_fd_("'#'", 1);
	if (t->flags[3])
		ft_putstr_fd_("' '", 1);
	if (t->flags[4])
		ft_putstr_fd_("'+'", 1);
	ft_putstr_fd_("\n\twidth: ", 1);
	put_size_t_fd(t->width, 1);
	ft_putstr_fd_("\n\tprecision: ", 1);
	put_size_t_fd(t->precision, 1);
	ft_putstr_fd_("\n\thas precision: ", 1);
	put_size_t_fd(t->has_precision, 1);
	ft_putstr_fd_("\n\tconversion: ", 1);
	ft_putchar_fd_(t->conversion, 1);
	ft_putchar_fd_('\n', 1);
}

void	print_blanks(size_t amount, t_format *t)
{
	size_t	i;

	i = 0;
	while (i < amount)
	{
		count_put_char(' ', t);
		i ++;
	}
}

void	print_zeroes(size_t amount, t_format *t)
{
	size_t	i;

	i = 0;
	while (i < amount)
	{
		count_put_char('0', t);
		i ++;
	}
}

void	put_str_len(const char *str, size_t len, t_format *t)
{
	size_t	i;

	i = 0;
	while (str[i] && i < len)
	{
		count_put_char(str[i], t);
		i ++;
	}
}
