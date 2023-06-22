/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unwrap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define EMSG "ms: "

void	unwrap_envvars(t_list *iter)
{
	t_dict_int_str_member	*m;
	int						prev_type;

	prev_type = NONE;
	while (iter)
	{
		m = _member(iter);
		if (m->key == LITERAL && !(prev_type == HEREDOC))
			m->value = handle_env(m->value);
		prev_type = m->key;
		iter = iter->next;
	}
}

// can fail -> NULL, removes empty strings
t_list	*unwrap_quotes(t_list *iter, t_list **unwraped)
{
	t_dict_int_str_member	*m;
	char					**split;

	while (iter)
	{
		m = _member(iter);
		if (m->key == LITERAL && *(m->value))
		{
			split = ft_splitf(m->value, find_literal_end);
			while (*split != NULL)
				if (add_string(unwraped, *split++) == -1)
					return (NULL);
		}
		else if (m->key == LITERAL)
			;
		else
			insert_token_into_lst(m->key, m->value, unwraped, 0);
		iter = iter->next;
	}
	return (*unwraped);
}

//can fail if ambigous redirect
t_list	*unwrap_matches(t_list *iter, t_list **matched)
{
	t_dict_int_str_member	*m;
	t_list					*found;
	int						prev_type;

	prev_type = NONE;
	while (iter)
	{
		m = _member(iter);
		if (m->key == LITERAL && prev_type != HEREDOC)
		{
			found = NULL;
			add_wildmatches(&found, m->value);
			if (is_redir(prev_type) && ft_lstsize(found) > 1)
				return (printf(EMSG"%s: ambigous redirect\n", m->value), NULL);
			while (found)
				(insert_token_into_lst(LITERAL, found->content, matched, 0),
					found = found->next);
		}
		else
			insert_token_into_lst(m->key, m->value, matched, 0);
		prev_type = m->key;
		iter = iter->next;
	}
	return (*matched);
}

//can fail if no closing quotes or wildcard fails (ambigours redirect)
t_list	*unwrap(t_list *lexemes)
{
	t_list	*unwraped;
	t_list	*matched;

	unwraped = NULL;
	matched = NULL;
	unwrap_envvars(lexemes);
	if (unwrap_quotes(lexemes, &unwraped) == NULL)
		return (NULL);
	if (unwrap_matches(unwraped, &matched) == NULL)
		return (NULL);
	return (matched);
}
