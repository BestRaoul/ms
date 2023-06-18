/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotesplit2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	end_of_word(char c, char *s, int i)
{
	return (((ft_isspace(c) && ft_isspace(s[i]))
			|| (c == '"' && s[i] == '"') || (c == '\'' && s[i] == '\''))
		&& !ft_chr_escaped(i, s));
}

static int	next_token_ret(t_list **word, char **child_content,
							int len, int succeeded)
{
	char	*tmp;

	if (succeeded)
	{
		tmp = ft_tlst_to_str(*word);
		if (!tmp)
		{
			ft_lstclear(word, ft_delnode);
			return (-1);
		}
		*child_content = ft_powertrim(tmp, "");
		FREE(tmp);
		ft_lstclear(word, ft_delnode);
		return (len);
	}
	ft_lstclear(word, ft_delnode);
	return (-1);
}

/* slice by isspace */
static int	get_next_token(char *s, char **child_content)
{
	t_list	*word;
	char	c;
	int		i;

	i = 0;
	word = NULL;
	c = ' ';
	*child_content = NULL;
	while (ft_isspace(s[i]))
		i ++;
	while (s[i] && c != '!')
	{
		if (c == ' ' && s[i] == '"'
			&& !ft_chr_escaped(i, s))
			c = '"';
		else if (c == ' ' && s[i] == '\''
			&& !ft_chr_escaped(i, s))
			c = '\'';
		else if (end_of_word(c, s, i))
			c = '!';
		if (s[i] != ft_isspace(c) && !ft_lstadd_chr(s[i], &word))
			return (next_token_ret(&word, child_content, i, 0));
		i ++;
	}
	return (next_token_ret(&word, child_content, i, 1));
}

static int	add_next_word(char *str_, t_list **tokenlst)
{
	char	*child_content;
	int		added;

	child_content = NULL;
	if (ft_isblankstr(str_))
		return ((int) ft_strlen(str_));
	added = get_next_token(str_, &child_content);
	if (!child_content)
		return (-1);
	if (!ft_lstadd_str(child_content, tokenlst))
		return (-1);
	if (added == -1)
		return (-1);
	return (added);
}

char	**ft_quotesplit2(char *str)
{
	t_list	*tokenlst;
	size_t	i;
	char	**res;
	int		added;

	tokenlst = NULL;
	i = 0;
	while (i < ft_strlen(str))
	{
		added = add_next_word(str + i, &tokenlst);
		if (added == -1)
		{
			ft_lstclear(&tokenlst, ft_delnode);
			return (NULL);
		}
		i += added;
	}
	res = ft_tlst_to_strarr(tokenlst);
	ft_lstclear(&tokenlst, ft_delnode);
	if (!clean_qt2splt(&res))
		return (NULL);
	return (res);
}
