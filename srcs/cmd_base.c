/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:08:48 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/28 12:59:05 by obanshee         ###   ########.fr       */
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

char	**cmd_unsetenv(char *name, char **env)
{
	char	**env_new;
	int		i;
	int		j;
	size_t	len;

	if (!(len = ft_strlen(name)))
		return (env);
	i = 0;
	while (env[i])
		i++;
	if (!(env_new = set_array_2(i + 1)))
		return (env);
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (!(ft_strequ(env[i], name)))
			if (!(ft_strnequ(env[i], name, len) &&
				ft_strlen(env[i]) > len && env[i][len] == '='))
				env_new[j++] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	return (env_new);
}
