/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_more.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:35:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/21 17:53:00 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_program(char *prgm, char **env)
{
	char		*path;
	char		**path_array;
	struct stat	about;
	int			i;
	char		*var_path;

	if (ft_strchr(prgm, '/'))
		if (!access(prgm, F_OK))
		{
			stat(prgm, &about);
			if (!access(prgm, X_OK) && S_ISREG(about.st_mode))
				return (prgm);
		}
	var_path = var_from_env(env, "PATH");
	if (!var_path)
		return (NULL);
	path_array = ft_strsplit(var_path, ':');
	path = path_program_from_env(prgm, path_array);
	i = -1;
	while (path_array[++i])
		free(path_array[i]);
	free(path_array);
	if (!path)
		return (NULL);
	return (path);
}

int		nbr_args(char *cmd)
{
	int	len;
	int	quote;

	len = 1;
	quote = 0;
	while (*(cmd + 1))
	{
		if (*cmd == '"')
		{
			if (quote)
				quote = 0;
			else
				quote = 1;
		}
		if (!quote)
			if (*cmd == ' ' && *(cmd + 1) != ' ' && *(cmd + 1) != '\t')
				len++;
		cmd++;
	}
	return (len);
}

char	*one_arg(char *cmd)
{
	char	*word;
	int		i;

	i = 0;
	if (*cmd == '"')
	{
		cmd++;
		while (cmd[i] && cmd[i] != '"')
			i++;
	}
	else
		while (cmd[i] && cmd[i] != ' ')
			i++;
	word = ft_strnew(i + 1);
	word = ft_strncpy(word, *cmd == '"' ? cmd + 1 : cmd, i);
	return (word);
}

char	**cmd_arguments(char *cmd)
{
	char	**arguments;
	int		len;
	int		i;

	len = nbr_args(cmd);
	arguments = set_array_2(len + 1);
	i = 0;
	while (i < len)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		arguments[i] = one_arg(cmd);
		if (*cmd == '"')
			cmd++;
		cmd += ft_strlen(arguments[i]);
		if (*cmd == '"')
			cmd++;
		i++;
	}
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
