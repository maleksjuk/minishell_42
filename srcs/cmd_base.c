/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:08:48 by obanshee          #+#    #+#             */
/*   Updated: 2020/03/07 12:25:53 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		cmd_echo(char *str)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	output = ft_strdup(str);
	while (output[i + j])
	{
		if (output[i + j] == '"')
			j++;
		output[i] = output[i + j];
		i++;
	}
	output[i] = '\0';
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
		ft_printf("null\n");
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

void	cmd_unsetenv(char *name, t_env *env)
{
	t_env	*prev;

	prev = env;
	while (env)
	{
		if (ft_strequ(env->key, name))
		{
			prev->next = env->next;
			free(env->key);
			free(env->value);
			free(env->str);
			free(env);
			break;
		}
		prev = env;
		env = env->next;
	}
}
