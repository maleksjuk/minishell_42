/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:08:48 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/28 12:22:17 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_echo(char *str)
{
	ft_printf("%s\n", str);
	return (0);
}

int	cmd_cd(char *path)
{
	char	*current_path;
	char	*search_path;
	int		i;

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
	if (access(search_path, F_OK))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if (access(search_path, X_OK))
		ft_printf("cd: Permission denied: %s\n", path);
	else if (chdir(search_path))
		ft_printf("error cd\n");
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
		ft_printf("null\n");
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

int	cmd_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
