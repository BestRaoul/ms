/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:32:36 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/03 16:32:39 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	put_hex_fd(size_t n, int capitalize, int prefix, int fd)
{
	size_t	i;
	size_t	temp;
	char	*charset;
	char	*capital_charset;
	int		base;

	base = 16;
	charset = "0123456789abcdef";
	capital_charset = "0123456789ABCDEF";
	i = 0;
	if (prefix)
		ft_putstr_fd_("0x", fd);
	while (i < unsigned_num_width_size_t(n, base))
	{
		temp = (n / size_t_pow(base,
					unsigned_num_width_size_t(n, base) - i - 1)) % base;
		if (capitalize)
			ft_putchar_fd_(capital_charset[temp], fd);
		else
			ft_putchar_fd_(charset[temp], fd);
		i ++;
	}
}
