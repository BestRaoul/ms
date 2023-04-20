/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_size_t.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_size_t(size_t i, t_list **lst)
{
	t_list	*child;
	size_t	*content;

	content = malloc(sizeof(*content));
	if (!content)
		return (0);
	*content = i;
	child = ft_lstnew(content);
	if (!child)
	{
		free(content);
		return (0);
	}
	ft_lstadd_back(lst, child);
	return (1);
}
