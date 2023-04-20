/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_size_t_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:03:09 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/10 16:03:10 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	put_size_t_fd(size_t n, int fd)
{
	size_t	i;
	size_t	temp;
	char	*charset;
	int		base;

	base = 10;
	charset = "0123456789";
	i = 0;
	while (i < unsigned_num_width_size_t(n, base))
	{
		temp = (n / size_t_pow(base,
					unsigned_num_width_size_t(n, base) - i - 1)) % base;
		ft_putchar_fd_(charset[temp], fd);
		i ++;
	}
}
