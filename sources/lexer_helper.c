/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	insert_token_into_lst(enum TokenTypes type, char *value, t_list **lst)
{
	t_dict_int_str_member	*member;
	t_list					*new;

	member = t_dict_int_str_member_init(type, value);
	if (!member)
		return (0);
	new = ft_lstnew(member);
	if (!new)
	{
		t_dict_int_str_member_free(member);
		return (0);
	}
	ft_lstadd_back(lst, new);
	return (1);
}

t_list	*scan_tokens(char *s)
{
	t_list	*res;
	int		i;
	int		start;

	(void) start;
	//start = 0;
	i = 0;
	while (s[i])
	{

		i ++;
	}
	res = NULL;
	return (res);
}
