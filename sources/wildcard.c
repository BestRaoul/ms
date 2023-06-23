/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "TODO: wildcard: "

//returns count of matches added
int	add_wildmatches_in_dir(char *dirname, t_list **lst, char *pattern)
{
	struct dirent	*dir;
	DIR				*d;
	int				count;

	if (!in('*', pattern))
		return (0);
	d = opendir(dirname);
	if (d == NULL)
		crash();
	count = 0;
	dir = readdir(d);
	while (dir != NULL)
	{
		if (dir->d_name[0] != '.' && match(dir->d_name, pattern))
		{
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(dir->d_name)));
			count++;
		}
		dir = readdir(d);
	}
	closedir(d);
	return (count);
}

void	add_wildmatches(t_list **lst, char *pattern)
{
	int	count;

	count = add_wildmatches_in_dir(".", lst, pattern);
	if (count == 0)
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(pattern)));
}
