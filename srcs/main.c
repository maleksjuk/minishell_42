/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/28 13:53:33 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	proccess(char *cmd)
{
	ft_printf("%s", cmd);
	// if (execve(cmd, NULL, NULL) == -1)
	// 	ft_printf("errno = %i\n", errno);
	return (0);
}

int	check_cmd(char *str, char ***env)
{
	if (ft_strnequ(str, "echo", 4))
		cmd_echo(str + 5);
	else if (ft_strnequ(str, "cd", 2))
		cmd_cd(str + 3);
	else if (ft_strequ(str, "pwd"))
		cmd_pwd();
	else if (ft_strequ(str, "env"))
		cmd_env(*env);
	else if (ft_strnequ(str, "setenv", 6))
		*env = cmd_setenv(str + 7, *env);
	else
		proccess(str);
	return (0);
}

char	**get_env(char **envp)
{
	char	**env;
	int		len;

	len = 0;
	while (envp[len++]);
	if (!(env = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	env[len] = NULL;
	len = -1;
	while (envp[++len])
		env[len] = ft_strdup(envp[len]);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*bufer;
	char	**env;

	env = get_env(envp);
	if (!env)
		return (1);
	while (1)
	{
		ft_printf("$> ");
		bufer = ft_strnew(LEN_PATH);
		// read(0, bufer, count);
		get_next_line(0, &bufer);
		if (!ft_strequ(bufer, ""))
		{
			if (ft_strnequ(bufer, "exit", 4))
				exit(0);
			check_cmd(bufer, &env);
		}
		free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
