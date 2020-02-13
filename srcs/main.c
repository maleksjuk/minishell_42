/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/13 13:26:09 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		error_message(char *str, char *file)
{
	ft_printf("msh: %s: %s\n", str, file);
	return (0);
}

int		check_cmd(char *cmd, char ***env)
{
	char	*str;

	str = check_symbols(cmd, *env);
	printf("command: |%s|\n", str);
	if (!str)
		return (0);
	else if (!*str)
		return (0);
	if (ft_strnequ(str, "echo", 4))
		cmd_echo(str + 5);
	else if (ft_strnequ(str, "cd", 2))
		cmd_cd(*env, ft_strlen(str) > 2 ? str + 3 : NULL);
	else if (ft_strequ(str, "pwd"))
		cmd_pwd();
	else if (ft_strequ(str, "env"))
		cmd_env(*env);
	else if (ft_strnequ(str, "setenv", 6))
		*env = cmd_setenv(str + 7, *env);
	else if (ft_strnequ(str, "unsetenv", 8))
		*env = cmd_unsetenv(str + 9, *env);
	else
		cmd_more(str, *env);
	return (0);
}

char	**get_env(char **envp)
{
	char	**env;
	int		len;

	len = 0;
	while (envp[len++]);
	env = set_array_2(len + 1);
	len = -1;
	while (envp[++len])
		env[len] = ft_strdup(envp[len]);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*bufer;
	char	**env;

	ft_printf("\t$_*_$_*_$_*_$_*_$ MINISHELL $_*_$_*_$_*_$_*_$\n");
	ft_printf("\t$_*_$_*_$_*_$_*_$ welcome   $_*_$_*_$_*_$_*_$\n");
	env = get_env(envp);
	if (!env)
		return (1);
	while (1)
	{
		ft_printf("\tminishell_$ ");
		bufer = ft_strnew(LEN_PATH);
		// read(0, bufer, count);
		get_next_line(0, &bufer);
		if (!ft_strequ(bufer, ""))
		{
			if (ft_strnequ(bufer, "exit", 4))
			{
				ft_printf("\texit\n");
				ft_printf("\t$_*_$_*_$_*_$_*_$ MINISHELL $_*_$_*_$_*_$_*_$\n");
				ft_printf("\t$_*_$_*_$_*_$_*_$  good bye $_*_$_*_$_*_$_*_$\n");
				exit(0);
			}
			check_cmd(bufer, &env);
		}
		free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
