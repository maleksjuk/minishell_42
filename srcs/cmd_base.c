/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:08:48 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/29 12:16:04 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_quote_echo(char c, int quote[2])
{
	if (c == '\'' && quote[1] == 0)
	{
		quote[0] = !quote[0];
		return (1);
	}
	else if (c == '"' && quote[0] == 0)
	{
		quote[1] = !quote[1];
		return (1);
	}
	return (0);
}

int		cmd_echo(char *str)
{
	int		i[2];
	char	*output;
	int		quote[2];

	i[0] = 0;
	i[1] = 0;
	quote[0] = 0;
	quote[1] = 0;
	output = ft_strdup(str);
	while (output[i[0] + i[1]])
	{
		i[1] += check_quote_echo(output[i[0] + i[1]], quote);
		output[i[0]] = output[i[0] + i[1]];
		i[0]++;
	}
	output[i[0]] = '\0';
	ft_printf("%s\n", output);
	free(output);
	return (0);
}

int		cmd_pwd(void)
{
	char	*path;

	path = ft_strnew(LEN_PATH);
	path = getcwd(path, LEN_PATH);
	if (!path)
		error_message("getcwd", "error");
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

int		cmd_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s\n", env->str);
		env = env->next;
	}
	return (0);
}

void	cmd_unsetenv(char *key, t_env *env)
{
	t_env	*prev;

	prev = env;
	while (env)
	{
		if (ft_strequ(env->key, key))
		{
			prev->next = env->next;
			free_one_env(env);
			break ;
		}
		prev = env;
		env = env->next;
	}
}
