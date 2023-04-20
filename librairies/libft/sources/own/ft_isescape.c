/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isescape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
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

static int	insidesinglequotes(int pos, char *str)
{
	int	cursor;
	int	first_single_found;
	int	second_single_found;

	cursor = pos - 1;
	first_single_found = 0;
	second_single_found = 0;
	while (cursor >= 0 && first_single_found == 0)
	{
		if (ft_chareq(cursor, str, '\'')
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

/* tells if a char at a given pos is a valid escape char */
int	ft_isescape(int pos, char *str)
{
	int	backslash_cnt;

	if (str[pos] != '\\')
		return (0);
	if (insidesinglequotes(pos, str))
		return (0);
	backslash_cnt = prebackcnt(pos, str);
	return (backslash_cnt % 2 == 0);
}
