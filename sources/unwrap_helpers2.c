/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unwrap2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

static char	*loop1(char *s)
{
	char	*temp;
	int		i;

	temp = ft_strdup(s);
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\\' && temp[i + 1] == '*')
		{
			ft_memmove(temp + i, temp + i + 1, len(temp + i + 1));
			temp[len(temp) - 1] = 0;
			i--;
		}
		i++;
	}
	return (temp);
}

void	unmark_ignored_stars(t_list *iter)
{
	t_dict_int_str_member	*m;

	while (iter)
	{
		m = _member(iter);
		if (m->key == LITERAL)
			m->value = loop1(m->value);
		iter = iter->next;
	}
}

static char	*loop2(char *s, int i, int q_toggle)
{
	char	*temp;

	temp = ft_calloc(len(s) + 1 + count('*', s), sizeof(char));
	ft_strlcpy(temp, s, len(s) + 1);
	while (temp[i])
	{
		if (temp[i] == '\'' || temp[i] == '\"')
		{
			if (i == 0 || temp[i - 1] != '\\')
			{
				if (q_toggle == 0)
					q_toggle = temp[i];
				else if (temp[i] == q_toggle)
					q_toggle = 0;
			}
		}
		if (q_toggle != 0 && temp[i] == '*')
		{
			ft_memmove(temp + i + 1, temp + i, len(temp + i));
			temp[i] = '\\';
			i++;
		}
		i++;
	}
	return (temp);
}

void	mark_ignored_stars(t_list *iter)
{
	t_dict_int_str_member	*m;

	while (iter)
	{
		m = _member(iter);
		if (m->key == LITERAL)
			m->value = loop2(m->value, 0, 0);
		iter = iter->next;
	}
}
