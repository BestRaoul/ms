/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_append_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarr_append_str(char ***strarr, char *str)
{
	char	**res;
	int		i;
	t_list	*lst;
	char	*tmp;

	lst = NULL;
	i = 0;
	while ((*strarr)[i])
	{
		tmp = ft_strdup((*strarr)[i]);
		if (!tmp)
		{
			ft_lstclear(&lst, ft_delnode);
			return (0);
		}
		if (!ft_lstadd_str(tmp, &lst))
		{
			free(tmp);
			ft_lstclear(&lst, ft_delnode);
			return (0);
		}
		i ++;
	}

	tmp = ft_strdup(str);
	if (!ft_lstadd_str(tmp, &lst))
	{
		free(tmp);
		ft_lstclear(&lst, ft_delnode);
		return (0);
	}

	res = ft_tlst_to_strarr(lst);
	ft_lstclear(&lst, ft_delnode);
	if (!res)
	{
		ft_lstclear(&lst, ft_delnode);
		return (0);
	}
	free_arr((void **) *strarr);
	*strarr = res;
	return (1);
}
