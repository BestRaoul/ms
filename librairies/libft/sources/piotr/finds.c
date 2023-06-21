/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:20:59 by pkondrac          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:27 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in(char c, char *str)
{
	if (ft_find(c, str) != -1)
		return (1);
	return (0);
}

/* 
 * Returns length of string
 */
int	len(char *str)
{
	return (ft_strlen(str));
}

//else -1
int ft_find(char c, const char *str)
{
    int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/* 
 * Returns index of first occurence of C, else LEN
 */
int	find(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/* 
 * Returns index of first occurence of UNSECAPED-char, else -1
 */
int	find_noescape(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			if (i == 0 || str[i - 1] != '\\')
				return (i);
		}
		i++;
	}
	return (i);
}

/* 
 * Returns index of first occurence of UNSECAPED-char in cs, else LEN
 */
int	finds_noescape(char *cs, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (in(str[i], cs))
		{
			if (i == 0 || str[i - 1] != '\\')
				return (i);
		}
		i++;
	}
	return (i);
}

/* 
 * returns next match of UN-\ in STR
 else LEN
 */
int	findf_noescape(int (*match)(char), char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (match(str[i]))
		{
			if (i == 0 || str[i - 1] != '\\')
				return (i);
		}
		i++;
	}
	return (i);
}

//returns next MATCH-ing UN-\ UN-'-"
//else LEN
int	findf_ne_nq(int (*match)(char), char *s)
{
    int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
        {
			i += find_noescape(s[i], &(s[i + 1])) + 1;
            if (i == len(s))
                break;
        }
		if (match(s[i]))
			if (i == 0 || s[i - 1] != '\\')
				break;
		i++;
	}
	return (i);
}

//returns next char in cs UN-\ UN-'-"
//else LEN
int	finds_ne_nq(char *cs, char *s)
{
    int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
        {
			i += find_noescape(s[i], &(s[i + 1])) + 1;
            if (i == len(s))
                break;
        }
		if (in(s[i], cs))
			if (i == 0 || s[i - 1] != '\\')
				break;
		i++;
	}
	return (i);
}

//returns next C of UN-\ and UN-QUOTES
//else LEN
int	find_ne_nqs(char c, char *s, char *quotes)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (in(s[i], quotes))
		{
			i += find_noescape(s[i], &(s[i + 1])) + 1;
            if (i == len(s))
                break;
        }
		if (s[i] == c)
			if (i == 0 || s[i - 1] != '\\')
				break;
		i++;
	}
	return (i);
}

/* 
 * Returns index of first matching char, else LEN
 */
int	findf(int (*match)(char), char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (match(str[i]))
			return (i);
		i++;
	}
	return (i);
}

/* 
 * Returns index of first NON-matching char, else LEN
 */
int	findf_nt(int (*match)(char c), char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (match(str[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}
