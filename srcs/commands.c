/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:08:48 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/30 10:31:22 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_echo(char *str)
{
	ft_printf("\t%s\n", str);
	return (0);
}

int	cmd_cd(char *path)
{
	char	*current_path;
	char	*search_path;
	int		i;
	struct stat	about;

	current_path = ft_strnew(LEN_PATH);
	current_path = getcwd(current_path, LEN_PATH);
	i = 0;
	while (current_path[i])
		i++;
	if (i >= LEN_PATH)
		return (1);
	current_path[i] = '/';
	if (path[0] != '/')
		search_path = ft_strjoin(current_path, path);
	else
		search_path = ft_strdup(path);
	if (stat(search_path, &about))
		ft_printf("EAGAIN\n");
	else if (access(search_path, F_OK))
		ft_printf("\tcd: no such file or directory: %s\n", path);
	else if (!S_ISDIR(about.st_mode))
		ft_printf("\tcd: not a directory: %s\n", path);
	else if (access(search_path, X_OK))
		ft_printf("\tcd: permission denied: %s\n", path);
	else if (chdir(search_path))
		ft_printf("\terror cd\n");
	free(current_path);
	free(search_path);
	return (0);
}

int	cmd_pwd(void)
{
	char	*path;

	path = ft_strnew(LEN_PATH);
	path = getcwd(path, LEN_PATH);
	if (!path)
		ft_printf("\tnull\n");
	ft_printf("\t%s\n", path);
	free(path);
	return (0);
}

int	cmd_env(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
	{
		ft_printf("\t%s\n", env[i]);
		i++;
	}
	return (0);
}

char	**cmd_setenv(char *str, char **env)
{
	char	**env_new;
	int		i;

	i = 0;
	while (env[i++]);
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
	while (env[i++]);
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
