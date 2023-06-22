/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	**init_lookup(int m, int n)
{
	int	i;
	int	**t;

	t = ft_calloc(n + 1, sizeof(*t));
	i = 0;
	while (i < n + 1)
	{
		t[i] = ft_calloc(m + 1, sizeof(**t));
		i ++;
	}
	t[0][0] = 1;
	return (t);
}

void	init_first_row(int m, int **t, char *pattern)
{
	int	i;

	i = 1;
	while (i < m + 1)
	{
		if (pattern[i - 1] == '*')
			t[0][i] = t[0][i - 1];
		i ++;
	}
}

void	logic(int ij[2], int **t, char *str, char *pattern)
{
	int	i;
	int	j;

	i = ij[0];
	j = ij[1];
	if (pattern[j - 1] == '*')
		t[i][j] = t[i][j - 1] || t[i - 1][j];
	else if (str[i - 1] == pattern[j - 1])
		t[i][j] = t[i - 1][j - 1];
	else
		t[i][j] = 0;
}

int	free_lookup(int m, int n, int **t)
{
	int	i;
	int	res;

	res = t[n][m];
	i = 0;
	while (i < n + 1)
	{
		FREE(t[i]);
		i ++;
	}
	FREE(t);
	return (res);
}

/* implementation source:
 * https://www.geeksforgeeks.org/wildcard-pattern-matching/ */
/* approach explanation: https://www.youtube.com/watch?v=Ak_GhOHkf8A */
int	match(char *str, char *pattern)
{
	int	m;
	int	n;
	int	**t;
	int	ij[2];

	m = len(pattern);
	n = len(str);
	if (m == 0)
		return (n == 0);
	t = init_lookup(m, n);
	init_first_row(m, t, pattern);
	ij[0] = 1;
	while (ij[0] < n + 1)
	{
		ij[1] = 1;
		while (ij[1] < m + 1)
		{
			logic(ij, t, str, pattern);
			ij[1]++;
		}
		ij[0]++;
	}
	return (free_lookup(m, n, t));
}
