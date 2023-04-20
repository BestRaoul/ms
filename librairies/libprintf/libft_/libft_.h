/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT__H
# define LIBFT__H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

int		ft_isdigit_(int c);
size_t	ft_strlen_(const char *s);
void	ft_putchar_fd_(char c, int fd);
void	ft_putstr_fd_(char *s, int fd);
void	ft_putnbr_fd_(int n, int fd);
int		my_abs_(int a);
void	*ft_calloc_(size_t nmemb, size_t size);
void	*ft_memset_(void *s, int c, size_t n);
void	ft_bzero_(void *s, size_t n);
int		ft_atoi_(const char *nptr);

#endif
