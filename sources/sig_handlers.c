/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 12:42:36 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	handler_c(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	(void) sig;
	if (g_.is_sig == -1)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		write(2, "^C\n", 3);
		g_.is_sig = 1;
	}
}

void	handler_slash(int sig, siginfo_t *info, void *context)
{
	if (g_.is_sig != -1)
	{
		write(2, "^\\Quit: 3\n", 10);
		g_.is_sig = 2;
	}
	if (g_.is_sig == -1)
	{
		rl_redisplay();
	}
	(void) sig;
	(void) info;
	(void) context;
}
