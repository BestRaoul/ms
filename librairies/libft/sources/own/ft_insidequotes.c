/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insidequotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	prebackcnt(int pos, char *str)
{
	int	cnt;
	int	curpos;

	cnt = 0;
	curpos = pos - (cnt + 1);
	while (str[curpos] == '\\')
	{
		cnt ++;
		curpos = pos - (cnt + 1);
	}
	return (cnt);
}

int	ft_insidequotes(int pos, char *str, char quote)
{
	int	cursor;
	int	first_single_found;
	int	second_single_found;

	cursor = pos - 1;
	first_single_found = 0;
	second_single_found = 0;
	while (cursor >= 0 && first_single_found == 0)
	{
		if (ft_chareq(cursor, str, quote)
			&& prebackcnt(cursor, str) % 2 == 0)
			first_single_found = 1;
		cursor --;
	}
	cursor = pos + 1;
	while (cursor < (int)ft_strlen(str) && second_single_found == 0)
	{
		if (ft_chareq(cursor, str, '\'')
			&& prebackcnt(cursor, str) % 2 == 0)
			second_single_found = 1;
		cursor ++;
	}
	return (first_single_found && second_single_found);
}
