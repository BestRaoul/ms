/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *content is not a null terminated string, only a single char */
int	ft_lstadd_chr(char c, t_list **lst)
{
	t_list	*child;
	char	*content;

	content = MALLOC(sizeof(*content));
	if (!content)
		return (0);
	content[0] = c;
	child = ft_lstnew(content);
	if (!child)
	{
		free(content);
		return (0);
	}
	ft_lstadd_back(lst, child);
	return (1);
}
