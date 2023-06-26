/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "ms: "

//CDO: optimise to replace KEY by VAL
int	export(char **argv)
{
	int		crapped;
	char	*key;
	int		split;

	crapped = 0;
	argv++;
	while (*argv)
	{
		if (!export_valid(*argv))
		{
			ft_dprintf(2, ERROR_MSG"export: `%s': not a valid identifier\n",
				*argv);
			crapped = 1;
			argv++;
			continue ;
		}
		if (!in('=', *argv) && argv++)
			continue ;
		split = find('=', *argv);
		(*argv)[split] = '\0';
		key = &((*argv)[0]);
		add_var_to_env(key, &((*argv)[split + 1]));
		argv++;
	}
	return (crapped);
}

int	unset(char **argv)
{
	argv ++;
	while (*argv)
	{
		remove_var_from_env(*argv);
		argv ++;
	}
	return (0);
}

int	pwd_builtin(void)
{
	char	*pwdstr;

	pwdstr = getcwd(NULL, 0);
	if (!pwdstr)
	{
		ft_dprintf(2, ERROR_MSG"pwd: fatal error\n");
		return (2);
	}
	ft_printf("%s\n", pwdstr);
	garbage_collector(ADD, pwdstr);
	return (0);
}

int	env_builtin(void)
{
	print_env();
	return (0);
}

void	exit_builtin(char **argv)
{
	int	n;

	ft_dprintf(2, "exit\n");
	if (!argv || !argv[1])
		n = g_.status;
	else if (!ft_str_is_int(argv[1]))
	{
		ft_dprintf(2, "ms: exit: %s: numeric argument required\n", argv[1]);
		n = 255;
	}
	else
		n = ft_atoi(argv[1]);
	close_and_free_all();
	exit(n);
}
