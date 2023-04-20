/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:16:17 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/18 14:16:19 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*last_ptr;

	ptr = (char *)s;
	last_ptr = 0;
	while (*ptr)
	{
		if (*ptr == (char)c)
			last_ptr = ptr;
		ptr ++;
	}
	if (*ptr == (char)c)
		return (ptr);
	return (last_ptr);
}
