/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:56:19 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/21 11:56:20 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	starting_index(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	while (i < ft_strlen(s1))
	{
		j = 0;
		found = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
				found = 1;
			j ++;
		}
		if (!found)
			return (i);
		i ++;
	}
	return (ft_strlen(s1) - 1);
}

static size_t	ending_index(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		found;

	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		j = 0;
		found = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
				found = 1;
			j ++;
		}
		if (!found)
			return (i);
		i --;
	}
	return (0);
}

static int	char_in_str(char const *s1, const char c)
{
	while (*s1)
		if (*s1 ++ == c)
			return (1);
	return (0);
}

static char	*helper(char const *s1, const char *set)
{
	char	*res;
	int		non_sep_chars;

	non_sep_chars = 0;
	while (*s1)
		if (!char_in_str(set, *s1++))
			non_sep_chars ++;
	if (!non_sep_chars)
	{
		res = malloc(1);
		if (!res)
			return (0);
		res[0] = 0;
		return (res);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*res;
	size_t	i;

	start = starting_index(s1, set);
	res = helper(s1, set);
	if (res != 0)
		return (res);
	len = ending_index(s1, set) - start + 2;
	res = malloc(len);
	if (!res)
		return (0);
	s1 += start;
	i = 0;
	while (i < len - 1)
	{
		res[i] = s1[i];
		i ++;
	}
	res[i] = 0;
	return (res);
}
