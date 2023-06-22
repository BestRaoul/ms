/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

/*
 * Returns allocated string of all substrings joined
 */
char	*join(char **strr, char *joint)
{
	char	*res;
	int		final_size;
	int		i;

	final_size = 0;
	i = 0;
	while (strr[i] != NULL)
		final_size += len(strr[i++]) + len(joint);
	final_size -= len(joint);
	res = ft_calloc(final_size + 1, sizeof(char));
	i = 0;
	while (strr[i] != NULL)
	{
		ft_strlcpy(&res[len(res)], strr[i], len(strr[i]) + 1);
		i++;
		if (strr[i] != NULL)
			ft_strlcpy(&res[len(res)], joint, len(joint) + 1);
	}
	res[len(res)] = 0;
	return (res);
}

/* 
 * Returns count of a char occurences in string
 */
int	count(char c, char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		count += str[i] == c;
		i++;
	}
	return (count);
}

/* 
 * Returns allocated string (start inclusive, end inclusive)
 //printf("CHOP %c(%d) -> %c(%d)\n", str[0], 0, str[end], end);
 */
char	*chop(char *str, int end)
{
	char	temp;
	char	*res;

	if (end < 0)
		return (ft_strdup(""));
	temp = str[end + 1];
	str[end + 1] = 0;
	res = ft_strdup(str);
	str[end + 1] = temp;
	return (res);
}

/* 
 * Returns allocated string of first consecutive matching characters
 */
char	*_scan(char *str, int (*checker)(char c))
{
	int	i;

	i = findf_nt(checker, str);
	return (chop(str, i - 1));
}

/* 
 * Returns allocated string of first consecutive NON-matching characters
 */
char	*_scan_nt(char *str, int (*checker)(char c))
{
	int	i;

	i = findf(checker, str);
	return (chop(str, i - 1));
}
