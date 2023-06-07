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
//#define malloc malloc(s) printf("%s %s %u %p", __FILE__, __LINE__, )

t_dict_int_str_member	*t_dict_int_str_member_init(int key, char *value)
{
	t_dict_int_str_member	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->key = key;
	if (value == NULL)
		res->value = NULL;
	else
	{
		res->value = malloc(sizeof(*(res->value)) * (ft_strlen(value) + 1));
		if (res->value == NULL)
		{
			free(res);
			return (NULL);
		}
		ft_strlcpy(res->value, value, ft_strlen(value) + 1);
		//ft_printf("allocated value (%s), %p\n", res->value, res->value);
	}
	return (res);
}

void	t_dict_int_str_member_free(t_dict_int_str_member * dict_int_str_member)
{
	if (dict_int_str_member->value != NULL)
	{
		//ft_printf("freeing value (%s), %p\n", dict_int_str_member->value, dict_int_str_member->value);
		free(dict_int_str_member->value);
	}
	free(dict_int_str_member);
}
