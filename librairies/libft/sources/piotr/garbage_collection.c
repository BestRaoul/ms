/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:20:59 by pkondrac          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:27 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_garbage {
	void *garbage;
	struct s_garbage *next;
} t_garbage;

void	free_garbage(t_garbage *g)
{
	if (g == NULL)
		return;
	if (g->next)
		free_garbage(g->next);
	if (g->garbage)
		free(g->garbage);
	free(g);
}

/*ADD -> adds PTR to garbage stack
FREE ALL -> frees all the garbage*/
void    *garbage_collector(int action, void *ptr)
{
	static t_garbage 	first = (t_garbage){NULL, NULL};
	static t_garbage 	*current = &first;
	t_garbage			*new;

	if (action == ADD)
	{
		write(1, "gc: add\n", 8);
		new = malloc(sizeof(t_garbage));
		if (new == NULL)
			return (NULL);
		new->garbage = ptr;
		new->next = NULL;
		current->next = new;
		current = new;
	}
	else if (action == FREE_ALL)
	{
		write(1, "gc: fa!\n", 8);
		free_garbage(first.next);
		first = (t_garbage){NULL, NULL};
		current = &first;
	}
	else
	{
		write(STDERR_FILENO, "GC: incorrect action\n", 21);
		exit(1);
	}
	return (ptr);
}

/*Allocate SIZE of bytes, and store in garbage collector*/
void *gc_malloc(size_t size)
{
	void    *p;
    int		err;

	p = malloc(size);
    if (p == NULL || garbage_collector(ADD, p) == NULL)
    {
		err = errno;
        perror("gc_malloc");
        exit(err);
    }
	return (p);
}