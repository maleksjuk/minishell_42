/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/22 16:41:09 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		error_message(char *str, char *file)
{
	ft_printf("msh: %s: %s\n", str, file);
	return (0);
}
//	check
int		cmd_more(char *cmd, char **env)
{
	char	*prgm;
	char	**argv;
	int		i;

	argv = cmd_arguments(cmd);
	prgm = cmd_program(argv[0], env);
	if (prgm)
	{
		cmd_system(prgm, argv, env);
		if (argv)
		{
			i = -1;
			while (argv[++i])
				if (argv[i])
					free(argv[i]);
			free(argv);
		}
		// free(prgm);
	}
	else
		error_message("command not found", argv[0]);
	return (0);
}

int		check_cmd(char *cmd, char ***env)
{
	char	*str;

	str = check_symbols(cmd, *env);
	if (!str || !*str)
		return (0);
	if (ft_strequ(str, "echo") || (ft_strnequ(str, "echo", 4) &&
		ft_strlen(str) > 4 && str[4] == ' '))
		cmd_echo(str + 5);
	else if (ft_strequ(str, "cd") || (ft_strnequ(str, "cd", 2) &&
		ft_strlen(str) > 2 && str[2] == ' '))
		*env = cmd_cd(env, ft_strlen(str) > 2 ? str + 3 : NULL);
	else if (ft_strequ(str, "pwd"))
		cmd_pwd();
	else if (ft_strequ(str, "env"))
		cmd_env(*env);
	else if (ft_strequ(str, "setenv") || (ft_strnequ(str, "setenv", 6) &&
		ft_strlen(str) > 6 && str[6] == ' '))
		*env = cmd_setenv(str + 7, *env);
	else if (ft_strequ(str, "unsetenv") || (ft_strnequ(str, "unsetenv", 8) &&
		ft_strlen(str) > 8 && str[8] == ' '))
		*env = cmd_unsetenv(str + 9, *env);
	else
		cmd_more(str, *env);
	free(str);
	return (0);
}

char	**get_env(char **envp)
{
	char	**env;
	int		len;

	if (!envp)
		return (NULL);
	len = 0;
	while (envp[len])
		len++;
	env = set_array_2(len + 1);
	if (!env)
		return (NULL);
	len = -1;
	while (envp[++len])
		env[len] = ft_strdup(envp[len]);
	return (env);
}

void	cmd_exit(char **env, char *bufer)
{
	int	i;

	ft_printf("exit\n* * * MINISHELL [end] * * *\n");
	free(bufer);
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	exit(0);
}

int		main(int argc, char **argv, char **envp)
{
	char	*bufer;
	char	**env;

	env = get_env(envp);
	if (!env)
		return (error_message("error", "null env"));
	ft_printf("* * * MINISHELL [begin] * * *\n");
	while (1)
	{
		ft_printf("---minishell$ ");
		bufer = ft_strnew(LEN_PATH);
		get_next_line(0, &bufer);
		if (!ft_strequ(bufer, ""))
		{
			if (ft_strequ(bufer, "exit") || (ft_strnequ(bufer, "exit", 4) &&
				ft_strlen(bufer) > 4 && bufer[4] == ' '))
				cmd_exit(env, bufer);
			check_cmd(bufer, &env);
		}
		free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
