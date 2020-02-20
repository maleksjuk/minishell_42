/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:08:48 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/20 13:10:24 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		cmd_echo(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == '"')
			j++;
		str[i] = str[i + j];
		i++;
	}
	str[i] = '\0';
	ft_printf("%s\n", str);
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

int		cmd_env(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

char	**cmd_setenv(char *str, char **env)
{
	char	**env_new;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_new = set_array_2(i + 2);
	env_new[i - 1] = ft_strdup(str);
	i = -1;
	while (env[++i])
		env_new[i] = ft_strdup(env[i]);
	return (env_new);
}

char	**cmd_unsetenv(char *name, char **env)
{
	char	**env_new;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
		i++;
	env_new = set_array_2(i - 1);
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (ft_strnequ(env[i], name, len))
			continue ;
		env_new[j] = ft_strdup(env[i]);
		j++;
	}
	return (env_new);
}
