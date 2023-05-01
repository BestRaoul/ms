/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

/* warning, this will return 0 if char not found */
size_t	get_chr_index(char needle, char *haystack)
{
	size_t	i;

	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle)
			return (i);
		i ++;
	}
	return (0);
}

/* returns NULL-terminated strarray with all possible matches */
char	**wildmatches(char *token, char *cwd)
{
	DIR				*d;
	struct dirent	*dir;
	size_t			i;
	size_t			j;

	d = opendir(cwd);
	if (!d)
		return (NULL);
	printf("matching for pattern `%s`\n", token);
	while ((dir = readdir(d)) != NULL) {
		printf("matching `%s`...\n", dir->d_name);
		i = 0;
		j = 0;
		while (i < ft_strlen(token))
		{
			if (token[i] == '*' && !ft_chr_escaped((int)i, token))
			{
				char next_chr = token[i + 1];
				if (next_chr == '\0')
				{
					j = ft_strlen(dir->d_name);
					break ;
				}
				if (!ft_chr_in_str(next_chr, dir->d_name))
					break ;
				j += get_chr_index(next_chr, dir->d_name + j) /*+ 1*/;
			}
			else
			{
				if (ft_isescape((int)i, token))
					i ++;
				if (token[i] != dir->d_name[j])
					break ;
				j ++;
			}
			i ++;
		}
		if (j == ft_strlen(dir->d_name))
			printf("match!\n");
	}
	closedir(d);
	return (NULL);
}
