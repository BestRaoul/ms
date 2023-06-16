/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:18:02 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/21 15:18:04 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "stdio.h"

int	count_words(char const *str, char sep)
{
	int	i;
	int	same_word;

	i = 0;
	same_word = 0;
	while (*str)
	{
		if (*str == sep)
			same_word = 0;
		else
		{
			if (!same_word)
			{
				same_word = 1;
				i ++;
			}
		}
		str ++;
	}
	return (i);
}

static size_t	next_wordlen(char const *str, char sep)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == sep)
			return (i);
		else
			i ++;
		str ++;
	}
	return (i);
}

static int	free_split(char ***res, int index)
{
	int	i;

	if ((*res)[index])
		return (0);
	i = 0;
	while (i < index)
	{
		FREE((*res)[i]);
		i ++;
	}
	FREE(res);
	return (1);
}

static char	**handle_empty(void)
{
	char	**res;

	res = MALLOC(sizeof(*res));
	if (!res)
		return (0);
	res[0] = 0;
	return (res);
}

char	**ft_split(char const *str, char sep)
{
	char	**res;
	int		i;

	if (!count_words(str, sep))
		return (handle_empty());
	res = MALLOC(sizeof(*res) * (count_words(str, sep) + 1));
	if (!res)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str != sep)
		{
			res[i] = MALLOC(next_wordlen(str, sep) + 1);
			if (free_split(&res, i))
				return (0);
			ft_strlcpy(res[i], str, next_wordlen(str, sep) + 1);
			i ++;
			str += next_wordlen(str, sep);
		}
		else
			str ++;
	}
	res[i] = 0;
	return (res);
}
