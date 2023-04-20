/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotesplit2_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	spcchr(char c)
{
	return (c == '\'' || c == '"' || c == '\\');
}

static int	last_if(char *str, int i, t_list **word)
{
	return ((!spcchr(str[i]) || ft_insidequotes(i, str, '\'')
			|| ft_insidequotes(i, str, '"'))
		&& !ft_lstadd_chr(str[i], word));
}

char	*replace_escapes(char *str)
{
	t_list	*word;
	int		i;
	int		previous_was_bckslsh;

	word = NULL;
	i = 0;
	previous_was_bckslsh = 0;
	while (i < (int) ft_strlen(str))
	{
		if (spcchr(str[i]) && previous_was_bckslsh)
		{
			if (!ft_lstadd_chr(str[i], &word))
				return (ft_qtsplt2_ret(&word, NULL));
			previous_was_bckslsh = 0;
		}
		else if (str[i] == '\\' && !previous_was_bckslsh)
			previous_was_bckslsh = 1;
		else if (last_if(str, i, &word))
			return (ft_qtsplt2_ret(&word, NULL));
		i ++;
	}
	return (ft_qtsplt2_ret(&word, ft_tlst_to_str(word)));
}

static int	clean_ret(char ***splt, t_list **nsplt, int success)
{
	char	**res;

	if (success)
	{
		res = ft_tlst_to_strarr(*nsplt);
		ft_free_split(*splt, ft_strarrlen(*splt));
		*splt = res;
		ft_lstclear(nsplt, ft_delnode);
		return (1);
	}
	ft_free_split(*splt, ft_strarrlen(*splt));
	ft_lstclear(nsplt, ft_delnode);
	return (0);
}

int	clean_qt2splt(char ***splt)
{
	t_list	*newsplt;
	int		i;
	char	*clean;

	newsplt = NULL;
	i = 0;
	while ((*splt)[i])
	{
		clean = replace_escapes((*splt)[i]);
		if (!clean)
			return (clean_ret(splt, &newsplt, 0));
		if (ft_strlen(clean) > 0 && !ft_lstadd_str(clean, &newsplt))
			return (clean_ret(splt, &newsplt, 0));
		if (ft_strlen(clean) == 0)
			free(clean);
		i ++;
	}
	return (clean_ret(splt, &newsplt, 1));
}
