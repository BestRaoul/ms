/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinpaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lst_add_first(const char *frst, t_list **lst)
{
	int		had_sep;
	char	*blank_trimmed;
	char	*all_trimmed;
	char	*sep_joined;

	blank_trimmed = ft_powertrim(frst, "");
	if (!blank_trimmed)
		return (0);
	had_sep = blank_trimmed[0] == ft_getsep();
	all_trimmed = ft_powertrim_chr(blank_trimmed, ft_getsep());
	gc_free(blank_trimmed);
	if (!all_trimmed)
		return (0);
	if (had_sep)
	{
		sep_joined = ft_strjoin_chr_str(ft_getsep(), all_trimmed);
		gc_free(all_trimmed);
		if (!sep_joined)
			return (0);
		return (ft_lstadd_str(sep_joined, lst));
	}
	else
		return (ft_lstadd_str(all_trimmed, lst));
}

static int	lst_add(const char *path, t_list **lst)
{
	char	*trimmed;

	trimmed = ft_powertrim_chr(path, ft_getsep());
	if (!trimmed)
		return (0);
	return (ft_lstadd_str(trimmed, lst));
}

static char	*proxy_ret(t_list **lst)
{
	char	*res;

	res = ft_str_tlst_to_str_join(*lst, ft_getsep());
	ft_lstclear(lst, ft_delnode);
	return (res);
}

/* Accepts NULL terminated list of paths */
char	*ft_joinpaths(const char *path, ...)
{
	va_list		ptr;
	t_list		*pth_lst;

	pth_lst = NULL;
	va_start(ptr, path);
	if (!path || !lst_add_first(path, &pth_lst))
	{
		ft_lstclear(&pth_lst, ft_delnode);
		return (NULL);
	}
	path = va_arg(ptr, const char *);
	while (path)
	{
		if (!ft_isblankstr(path) && !lst_add(path, &pth_lst))
		{
			ft_lstclear(&pth_lst, ft_delnode);
			va_end(ptr);
			return (NULL);
		}
		path = va_arg(ptr, const char *);
	}
	va_end(ptr);
	return (proxy_ret(&pth_lst));
}
