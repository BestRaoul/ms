/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "ms: "

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	return (ft_strequal(cmd, "echo") || ft_strequal(cmd, "cd")
		|| ft_strequal(cmd, "pwd") || ft_strequal(cmd, "export")
		|| ft_strequal(cmd, "unset") || ft_strequal(cmd, "env")
		|| ft_strequal(cmd, "exit") || ft_strequal(cmd, ".."));
}

char	**fake_cd_argv(char *pth)
{
	t_list	*lst;
	char	**res;

	lst = NULL;
	ft_lstadd_str("cd", &lst);
	ft_lstadd_str(pth, &lst);
	res = ft_tlst_to_strarr(lst);
	return (res);
}

int	exec_builtin(char *cmd, char **argv)
{
	if (g_.is_sig)
		return (1);
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
		exit_builtin(argv);
	if (ft_strequal(cmd, ".."))
		return (cd(fake_cd_argv("..")));
	return (1);
}

int	cd(char **argv)
{
	int	err;

	if (ft_strarrlen(argv) < 2)
	{
		if (ft_query_envp("HOME", g_.env))
			return (cd(fake_cd_argv(ft_query_envp("HOME", g_.env))));
		ft_dprintf(2, ERROR_MSG"cd: HOME not set\n");
		return (1);
	}
	if (ft_strarrlen(argv) > 2)
	{
		ft_dprintf(2, ERROR_MSG"cd: too many arguments\n");
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		err = errno;
		ft_dprintf(2, ERROR_MSG"cd: %s: %s\n", argv[1], strerror(errno));
		return (err);
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
	if (res != NULL && write(1, res, len(res)) == -1)
		crash();
	if (i == 1 && write(1, "\n", 1) == -1)
		crash();
	return (0);
}
