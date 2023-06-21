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
	if (ft_strarrlen(argv) < 2)
	{
		if (ft_query_envp("HOME", g.env))
			return (cd(fake_cd_argv(ft_query_envp("HOME", g.env))));
		write(2, "minishell: cd: HOME not set\n", 28);
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


//TODO: $ or any non alpha start -> not identifier
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
		remove_var_from_env(*argv);
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

void	exit_builtin(char **argv) 
{
	argv ++;
	if (!*argv)
		exit(g.status);
	if (!ft_str_is_int(*argv))
		exit(2);
	exit(ft_atoi(*argv));
}
