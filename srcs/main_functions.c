/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:20:06 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/29 15:25:18 by obanshee         ###   ########.fr       */
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

char	*get_full_cmd(char *cmd, t_env *env)
{
	char	*str;
	char	*new_str;

	str = ft_strtrim(cmd);
	if (!str)
		return (NULL);
	if (ft_strequ(str, ""))
	{
		free(str);
		return (NULL);
	}
	new_str = ft_strtrim_into(str);
	if (!new_str)
		return (NULL);
	free(str);
	str = check_quotes(env, new_str, NULL);
	free(new_str);
	return (str);
}

int		cmd_processing(char *cmd, t_env *env)
{
	char	*str;
	char	*prgm;

	if (!(str = get_full_cmd(cmd, env)))
		return (0);
	// str = ft_strdup(cmd);
	if (!(prgm = get_name_or_key(str, ' ')))
		return (0);
	if (ft_strequ(prgm, "echo"))
		cmd_echo(str + 5);
	else if (ft_strequ(prgm, "cd"))
		cmd_cd(env, ft_strlen(str) > 2 ? str + 3 : NULL);
	else if (ft_strequ(prgm, "pwd"))
		cmd_pwd();
	else if (ft_strequ(prgm, "env"))
		cmd_env(env);
	else if (ft_strequ(prgm, "setenv"))
		cmd_setenv(str + 7, env);
	else if (ft_strequ(prgm, "unsetenv"))
		cmd_unsetenv(str + 9, env);
	else
		cmd_more(str, env);
	free(str);
	free(prgm);
	return (0);
}

void	cmd_exit(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free_one_env(env);
		env = next;
	}
	ft_printf("exit\n\033[1;7;32m* * * MINISHELL [exit] * * *\033[0m\n");
	exit(0);
}
