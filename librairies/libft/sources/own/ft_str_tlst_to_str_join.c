/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tlst_to_str_join.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	combined_len(t_list *lst)
{
	t_list	*iter;
	size_t	res;

	iter = lst;
	res = 0;
	while (iter)
	{
		res += ft_strlen(iter->content);
		iter = iter->next;
	}
	return (res);
}

static void	inc_cntrs(size_t *i, int *wc)
{
	(*i)++;
	(*wc)++;
}

static char	*create_arr(t_list *lst, char sep)
{
	t_list	*iter;
	size_t	i;
	int		wc;
	char	*res;

	res = MALLOC(sizeof(*res) * (combined_len(lst) + 1)
			+ ft_max_int(0, ft_lstsize(lst) - 1));
	if (!res)
		return (NULL);
	iter = lst;
	i = 0;
	wc = 0;
	while (iter)
	{
		ft_strlcpy(res + i, iter->content, ft_strlen(iter->content) + 1);
		i += ft_strlen(iter->content);
		if (wc < ft_lstsize(lst) - 1)
		{
			res[i] = sep;
			inc_cntrs(&i, &wc);
		}
		iter = iter->next;
	}
	res[i] = '\0';
	return (res);
}

/* Combines lst of null terminated strings into a string */
char	*ft_str_tlst_to_str_join(t_list *lst, char sep)
{
	if (!lst)
		return (NULL);
	if (ft_lstsize(lst) == 0)
		return (NULL);
	return (create_arr(lst, sep));
}
