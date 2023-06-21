/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lst_add(const char *word, t_list **lst)
{
	char	*dup;

	dup = ft_strdup(word);
	if (!dup)
		return (0);
	return (ft_lstadd_str(dup, lst));
}

static char	*proxy_ret(t_list **lst)
{
	char	*res;

	res = ft_str_tlst_to_str(*lst);
	ft_lstclear(lst, ft_delnode);
	return (res);
}

/* Accepts NULL terminated list of strings */
char	*ft_strjoin2(const char *word, ...)
{
	va_list		ptr;
	t_list		*word_lst;

	word_lst = NULL;
	va_start(ptr, word);
	if (!word || !lst_add(word, &word_lst))
	{
		ft_lstclear(&word_lst, ft_delnode);
		return (NULL);
	}
	word = va_arg(ptr, const char *);
	while (word)
	{
		if (!lst_add(word, &word_lst))
		{
			ft_lstclear(&word_lst, ft_delnode);
			va_end(ptr);
			return (NULL);
		}
		word = va_arg(ptr, const char *);
	}
	va_end(ptr);
	return (proxy_ret(&word_lst));
}
