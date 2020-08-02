/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:20:06 by obanshee          #+#    #+#             */
/*   Updated: 2020/03/01 13:38:20 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		error_message(char *str, char *file)
{
	ft_printf("msh: %s: %s\n", str, file);
	return (0);
}

int		cmd_more(char *cmd, t_env *env)
{
	char	*prgm;
	char	**argv;
	int		i;

	argv = cmd_arguments(cmd);
	prgm = cmd_program(argv[0], value_from_env(env, "PATH"));
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
		free(prgm);
	}
	else
		error_message("command not found", argv[0]);
	return (0);
}

int		check_cmd(char *cmd, t_env *env)
{
	char	*str;

	str = check_symbols(cmd, env);
	if (!str || !*str)
		return (0);
	if (ft_strequ(str, "echo") || (ft_strnequ(str, "echo", 4) &&
		ft_strlen(str) > 4 && str[4] == ' '))
		cmd_echo(str + 5);
	else if (ft_strequ(str, "cd") || (ft_strnequ(str, "cd", 2) &&
		ft_strlen(str) > 2 && str[2] == ' '))
		cmd_cd(env, ft_strlen(str) > 2 ? str + 3 : NULL);
	else if (ft_strequ(str, "pwd"))
		cmd_pwd();
	else if (ft_strequ(str, "env"))
		cmd_env(env);
	else if (ft_strequ(str, "setenv") || (ft_strnequ(str, "setenv", 6) &&
		ft_strlen(str) > 6 && str[6] == ' '))
		cmd_setenv(str + 7, env);
	else if (ft_strequ(str, "unsetenv") || (ft_strnequ(str, "unsetenv", 8) &&
		ft_strlen(str) > 8 && str[8] == ' '))
		cmd_unsetenv(str + 9, env);
	else
		cmd_more(str, env);
	free(str);
	return (0);
}

t_env	*create_one_env(char *str)
{
	t_env	*one;
	int		i;

	one = (t_env *)malloc(sizeof(t_env *));
	one->str = ft_strdup(str);
	i = 0;
	while (str[i] != '=')
		i++;
	one->key = ft_strnew(i);
	one->key = ft_strncpy(one->key, str, i);
	one->value = ft_strdup(&(str[i + 1]));
	one->next = NULL;
	return (one);
}

t_env	*get_env(char **envp)
{
	t_env	*env_begin;
	t_env	*env_prev;
	t_env	*env_curr;
	int		len;

	if (!envp || !envp[0])
		return (NULL);
	env_begin = create_one_env(envp[0]);
	env_prev = env_begin;
	len = 0;
	while (envp[++len])
	{
		env_curr = create_one_env(envp[len]);
		env_prev->next = env_curr;
		env_prev = env_curr;
	}
	return (env_begin);
}

void	cmd_exit(t_env *env, char *bufer)
{
	// t_env	*prev;

	free(bufer);
	while (env)
	{
		// if (env->key)
		// 	free(env->key);
		// if (env->value)
		// 	free(env->value);
		// if (env->str)
		// 	free(env->str);
		// prev = env;
		env = env->next; 
		// free(prev);
	}
	ft_printf("exit\n\033[1;7;32m* * * MINISHELL [exit] * * *\033[0m\n");
	exit(0);
}
