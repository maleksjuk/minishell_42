/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:40:11 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/20 13:10:56 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*helper_cd(char *path, char *current_path, int *i)
{
	struct stat	about;
	char		*search_path;

	while (current_path[*i])
		(*i)++;
	if (*i >= LEN_PATH)
		return (NULL);
	current_path[*i] = '/';
	if (path[0] != '/')
		search_path = ft_strjoin(current_path, path);
	else
		search_path = ft_strdup(path);
	if (stat(search_path, &about))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if (access(search_path, F_OK))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if (!S_ISDIR(about.st_mode))
		ft_printf("cd: not a directory: %s\n", path);
	else if (access(search_path, X_OK))
		ft_printf("cd: permission denied: %s\n", path);
	else
		*i = 0;
	return (search_path);
}

char	**cmd_cd(char ***env, char *path)
{
	char	*current_path;
	char	*search_path;
	int		flag;

	current_path = ft_strnew(LEN_PATH);
	current_path = getcwd(current_path, LEN_PATH);
	flag = 0;
	if (!path)
		search_path = var_from_env(*env, "HOME");
	else if (ft_strequ(path, "-"))
		search_path = var_from_env(*env, "OLDPWD");
	else if (!(search_path = helper_cd(path, current_path, &flag)))
		return (*env);
	if (chdir(search_path) && !flag)
		error_message("error", "cd");
	*env = cmd_unsetenv("OLDPWD", *env);
	*env = cmd_setenv(ft_strjoin("OLDPWD=", current_path), *env);
	*env = cmd_unsetenv("PWD", *env);
	*env = cmd_setenv(ft_strjoin("PWD=", search_path), *env);
	free(current_path);
	free(search_path);
	return (*env);
}
