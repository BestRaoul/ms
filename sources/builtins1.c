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
	res = ft_strarr_to_str(argv + i, ' ');
	if (res != NULL)
		ft_printf("%s", res);
	if (i == 1)
		ft_printf("\n");
	if (res)
		FREE(res);
	return (0);
}

char	*get_export_key(char *str)
{
	char	*res;
	char	**spltres;

	spltres = ft_split(str, '=');
	if (!spltres)
		return (NULL);
	if (ft_strarrlen(spltres) == 0)
	{
		free_arr((void **) spltres);
		return (NULL);
	}
	res = ft_strdup(spltres[0]);
	free_arr((void **) spltres);
	return (res);
}

char	*get_export_value(char *str)
{
	char	*res;
	char	*newval;

	if (ft_str_endswith(str, "="))
		return (ft_calloc(1, sizeof(*res)));
	res = ft_calloc(ft_strlen_int(str) - ft_strchr2(str, '=') + 1, sizeof(*res));
	ft_strlcpy(res, str + ft_strchr2(str, '='), ft_strlen_int(str) - ft_strchr2(str, '=') + 1);
	// TODO: env needs to be passed here probably
	newval = handle_env(res);
	FREE(res);
	return (newval);
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
		key = get_export_key(*argv);
		if (!key)
			return (1);
		val = get_export_value(*argv);
		if (!val)
			return (1);
		add_var_to_env(key, val);
		frees(2, key, val);
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
	free(pwdstr);
	return (0);
}

int	env_builtin()
{
	print_env();
	return (0);
}
