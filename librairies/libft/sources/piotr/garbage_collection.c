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

#define DEBUG_ALLOC 0

typedef struct s_garbage {
	void				*garbage;
	struct s_garbage	*next;
}	t_garbage;

void	free_garbage(t_garbage *g)
{
	if (g == NULL)
		return ;
	if (g->next)
		free_garbage(g->next);
	if (g->garbage)
		free(g->garbage);
	free(g);
}

void	print_gt(t_garbage *root)
{
	printf("(%p)", root->garbage);
	root = root->next;
	while (root != NULL)
	{
		printf(" -> (%p)", root->garbage);
		root = root->next;
	}
	printf("\n");
}

/*ADD -> adds PTR to garbage stack
REMOVE -> removes PTR from garbage stack
FREE ALL -> frees all the garbage*/
void	*garbage_collector(int action, void *ptr)
{
	static t_garbage	first = (t_garbage){NULL, NULL};
	static t_garbage	*current = &first;
	t_garbage			*new;
	static int			total = 0;

	if (action == ADD)
	{
		if (DEBUG_ALLOC) {
		write(1, "gc+ \n", 5); }
//		printf("P: %p\n", ptr);
		new = malloc(sizeof(t_garbage));
		if (new == NULL)
			return (NULL);
		new->garbage = ptr;
		new->next = NULL;
		current->next = new;
		current = new;

		total ++;
	}
	else if (action == REMOVE)
	{
		if (DEBUG_ALLOC) {
		write(1, "gc- \n", 5); }
//		printf("P: %p\n", ptr);
		t_garbage *i = first.next;
		t_garbage *prev = &first;
		while (i != NULL)
		{
			if (i->garbage == ptr)
				break;
			prev = i;
			i = i->next;
		}
		if (i == NULL)
		{
			dprintf(2, "P: %p\n", ptr);
			write(2, "gc: remove PTR not found.\n", 26);
			exit(127);
		}
		
		if (current == i)
			current = prev;
		prev->next = i->next;
		free(i);

		total --;
	}
	else if (action == FREE_ALL)
	{
		if (DEBUG_ALLOC) {
		write(1, "gc: fa!\n", 8); }
		free_garbage(first.next);
		first = (t_garbage){NULL, NULL};
		current = &first;

		total = 0;
	}
	else
	{
		write(STDERR_FILENO, "GC: incorrect action\n", 21);
		exit(1);
	}
	
	if (DEBUG_ALLOC) {
		print_gt(&first);
	printf("%d\n", total); }
	return (ptr);
}

/*Allocate SIZE of bytes, and store in garbage collector*/
void	*gc_malloc(const char* fname, int lineno, size_t size)
{
	void	*p;
    int		err;

	if (DEBUG_ALLOC)
	{ printf("m  %s:%d\n", fname, lineno); }
	p = malloc(size);
    if (p == NULL || garbage_collector(ADD, p) == NULL)
    {
		err = errno;
        perror("gc_malloc");
        exit(err);
    }
	return (p);
}

/*Frees PTR, and removes from garbage collector*/
void	gc_free(const char* fname, int lineno, void *ptr)
{
	if (DEBUG_ALLOC)
	{ printf("f  %s:%d\n", fname, lineno); }
    garbage_collector(REMOVE, ptr);
	free(ptr);
}