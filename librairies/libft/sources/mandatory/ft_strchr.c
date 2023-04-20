/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:55:21 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/17 17:55:22 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* buh needs to copy temporarily string to return a pointer. or not???? idk */

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	c2;

	c2 = (char)c;
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == c2)
			return (ptr);
		ptr ++;
	}
	if (*ptr == c2)
		return (ptr);
	return (0);
}
