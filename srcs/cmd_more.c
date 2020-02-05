/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_more.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:35:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/05 11:31:09 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_program_from_env(char *prgm, char **path_array)
{
	char		*path;
	int			i;
	char		*tmp;
	struct stat	about;

	path = NULL;
	i = -1;
	while (path_array[++i])
	{
		tmp = ft_strjoin(path_array[i], "/\0");
		path = ft_strjoin(tmp, prgm);
		free(tmp);
		if (!access(path, F_OK))
		{
			stat(path, &about);
			if (!access(path, X_OK) && S_ISREG(about.st_mode))
				break ;
		}
		free(path);
		path = NULL;
	}
	return (path);
}

char	*cmd_program(char *prgm, char **env)
{
	char		*path;
	char		**path_array;
	struct stat	about;
	int			i;

	if (!access(prgm, F_OK))
	{
		stat(prgm, &about);
		if (!access(prgm, X_OK) && S_ISREG(about.st_mode))
			return (prgm);
	}
	i = -1;
	while (env[++i])
		if (ft_strnequ(env[i], "PATH=", 5))
			break ;
	path_array = ft_strsplit(env[i] + 5, ':');
	path = path_program_from_env(prgm, path_array);
	i = -1;
	while (path_array[++i])
		free(path_array[i]);
	free(path_array);
	if (!path)
		return (NULL);
	return (path);
}

char	**cmd_arguments(char *cmd)
{
	char	**arguments;

	arguments = ft_strsplit(cmd, ' ');
	return (arguments);
}

int		cmd_system(char *prgm, char **argv, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		execve(prgm, argv, env);
		exit(-1);
	}
	if (waitpid(pid, &status, 0))
		return (-1);
	else if (WIFEXITED(status))
		return (WIFEXITED(status));
	return (-1);
}

int		cmd_more(char *cmd, char **env)
{
	char	*prgm;
	char	**argv;

	argv = cmd_arguments(cmd);
	prgm = cmd_program(argv[0], env);
	if (prgm)
		cmd_system(prgm, argv, env);
	else
		error_message("command not found", argv[0]);
	return (0);
}
