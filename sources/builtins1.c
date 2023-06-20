/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "ms_turtle"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	return (ft_strequal(cmd, "echo") || ft_strequal(cmd, "cd")
	|| ft_strequal(cmd, "pwd") || ft_strequal(cmd, "export")
	|| ft_strequal(cmd, "unset") || ft_strequal(cmd, "env")
	|| ft_strequal(cmd, "exit"));
}

int	exec_builtin(char *cmd, char **argv)
{
	if (ft_strequal(cmd, "echo"))
		return (echo(argv));
	if (ft_strequal(cmd, "cd"))
		return (cd(argv));
	if (ft_strequal(cmd, "pwd"))
		return (pwd_builtin());
	if (ft_strequal(cmd, "export"))
		return (export(argv));
	if (ft_strequal(cmd, "unset"))
		return (unset(argv));
	if (ft_strequal(cmd, "env"))
		return (env_builtin());
	if (ft_strequal(cmd, "exit"))
		return (ft_printf("todo exit\n"));
	return (1);
}

int	cd(char **argv)
{
	if (ft_strarrlen(argv) < 2)
	{
		write(2, "minishell: cd: not enough arguments\n", 36);
		return(1);
	}
	if (ft_strarrlen(argv) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return(1);
	}
	int status = chdir(argv[1]);
	if (status != 0)
	{
		perror(ERROR_MSG);
		return (status);
	}
	return (0);
}

int	echo(char **argv)
{
	int		i;
	char	*res;

	i = 1;
	if (ft_strarrlen(argv) >= 2 && ft_strequal(argv[1], "-n"))
		i = 2;
	res = NULL;
	if (argv[i] != NULL)
		res = join(&argv[i], " ");
	if (res != NULL)
		ft_printf("%s", res);
	if (i == 1)
		ft_printf("\n");
	return (0);
}

int	export(char **argv)
{
	char	*key;
	char	*val;

	argv ++;
	while (*argv)
	{
		if (!in('=', *argv))
		{
			argv ++;
			continue ;
		}
		if (ft_str_startswith(*argv, "="))
		{
			ft_printf("%s: export: `%s': not a valid identifier\n", ERROR_MSG, *argv);
			argv ++;
			continue ;
		}

		int split = find('=', *argv);
		(*argv)[split] = '\0';
		key = &((*argv)[0]);
		val = &((*argv)[split + 1]);
		if (find_in_env(key) != -1)
			remove_var_from_env(key); //TODO: optimise to replace KEY by VAL
		add_var_to_env(key, val);
		argv ++;
	}
	return (0);
}

int	unset(char **argv)
{
	argv ++;
	while (*argv)
	{
		if (!remove_var_from_env(*argv))
			return (1);
		argv ++;
	}
	return (0);
}

int	pwd_builtin()
{
	char	*pwdstr;

	pwdstr = getcwd(NULL, 0);
	if (!pwdstr)
	{
		ft_printf("fatal error\n");
		return (2);
	}
	ft_printf("%s\n", pwdstr);
	garbage_collector(ADD, pwdstr);
	return (0);
}

int	env_builtin()
{
	print_env();
	return (0);
}
