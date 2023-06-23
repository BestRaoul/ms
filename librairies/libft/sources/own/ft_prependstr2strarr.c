/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prependstr2strarr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_prependstr2strarr(char *str, char **arr)
{
	t_list	*one_lst;
	char	*strcp;
	char	**onearr;
	char	**res;

	one_lst = NULL;
	strcp = ft_strdup(str);
	if (!strcp)
		return (NULL);
	if (!ft_lstadd_str(strcp, &one_lst))
	{
		gc_free(strcp);
		return (NULL);
	}
	onearr = ft_tlst_to_strarr(one_lst);
	ft_lstclear(&one_lst, ft_delnode);
	if (!onearr)
		return (NULL);
	res = ft_strarrjoin(onearr, arr);
	ft_free_split(onearr, ft_strarrlen(onearr));
	return (res);
}
