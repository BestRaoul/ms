/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dict_int_str_member	*t_dict_int_str_member_init(int key, char *value)
{
	t_dict_int_str_member	*res;

	res = gc_malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->key = key;
	if (value == NULL)
		res->value = NULL;
	else
	{
		res->value = ft_strdup(value);
	}
	return (res);
}

void	t_dict_int_str_member_free(t_dict_int_str_member *dict_int_str_member)
{
	if (dict_int_str_member->value != NULL)
	{
		gc_free(dict_int_str_member->value);
	}
	gc_free(dict_int_str_member);
}
