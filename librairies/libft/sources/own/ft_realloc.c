/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:55:21 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/17 17:55:22 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc_gnl(void *src, size_t new_len)
{
	size_t	i;
	char	*ptr;
	char	*res;

	res = ft_calloc(1, new_len);
	if (res == NULL)
	{
		free(src);
		return (NULL);
	}
	i = 0;
	ptr = src;
	while (i < sizeof(src))
	{
		*(res + i) = *(ptr + i);
		i ++;
	}
	free(src);
	return (res);
}

int	*ft_realloc_intarr(int *src, size_t arr_size, size_t new_size)
{
	size_t	i;
	int		*res;

	if (new_size <= arr_size)
	{
		free(src);
		return (NULL);
	}
	res = ft_calloc(new_size, sizeof(int));
	if (res == NULL)
	{
		free(src);
		return (NULL);
	}
	i = 0;
	while (i < new_size)
	{
		res[i] = src[i];
		i ++;
	}
	free(src);
	return (res);
}

int	**fr_realloc_int2darr_part_two(int **src, int **res, const size_t sizes[3])
{
	size_t	i;
	size_t	j;

	res = ft_calloc(sizes[2], sizeof(*src));
	if (res == NULL)
	{
		j = 0;
		while (j < sizes[0])
		{
			free(src[j]);
			j ++;
		}
		free(src);
		return (NULL);
	}
	i = 0;
	while (i < sizes[2])
	{
		if (i < sizes[1])
			res[i] = src[i];
		else
			res[i] = ft_calloc(sizes[0], sizeof(**src));
		i ++;
	}
	return (res);
}

int	**ft_realloc_int2darr(int **src, size_t elem_size,
			size_t arr_size, size_t new_size)
{
	size_t			j;
	int				**res;
	const size_t	sizes[3] = {elem_size, arr_size, new_size};

	res = 0;
	if (new_size <= arr_size)
	{
		j = 0;
		while (j < elem_size)
		{
			free(src[j]);
			j ++;
		}
		free(src);
		return (NULL);
	}
	res = fr_realloc_int2darr_part_two(src, res, sizes);
	free(src);
	return (res);
}

char	*ft_realloc_chararr(char *src, size_t arr_size, size_t new_size)
{
	size_t	i;
	char	*res;

	if (new_size <= arr_size)
	{
		free(src);
		return (NULL);
	}
	res = ft_calloc(new_size, sizeof(char));
	if (res == NULL)
	{
		free(src);
		return (NULL);
	}
	i = 0;
	while (i < new_size)
	{
		res[i] = src[i];
		i ++;
	}
	free(src);
	return (res);
}
