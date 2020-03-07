/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 09:57:50 by obanshee          #+#    #+#             */
/*   Updated: 2020/03/07 12:27:41 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_array_2(int len)
{
	char	**array;
	int		i;

	if (!(array = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	i = 0;
	while (i < len)
		array[i++] = NULL;
	array[len - 1] = NULL;
	return (array);
}

char	*var_from_env(char **env, char *name)
{
	char	*var;
	int		i;

	i = -1;
	while (env[++i])
		if (ft_strnequ(env[i], name, ft_strlen(name)))
			if (env[i][ft_strlen(name)] == '=')
				break ;
	if (!env[i])
		return (NULL);
	var = ft_strdup(env[i] + ft_strlen(name) + 1);
	return (var);
}

char	**var_to_env(char **env, char *name, char *var)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strnequ(env[i], name, ft_strlen(name)))
			break ;
	if (!env[i])
		return (env);
	free(env[i]);
	env[i] = ft_strjoin(name, var);
	return (env);
}

char	*ft_strtrim_into(char *cmd)
{
	char	*dst;
	int		mas[2];
	char	*src;
	int		quote;

	src = ft_strtrim(cmd);
	if (!(dst = ft_strnew(ft_strlen(src) + 1)))
		return (NULL);
	mas[0] = 0;
	mas[1] = -1;
	quote = 0;
	while (src[++mas[1]])
	{
		if (src[mas[1]] == '"')
			quote = quote ? 0 : 1;
		if (!quote && (src[mas[1]] == ' ' || src[mas[1]] == '\t'))
		{
			if (!(src[mas[1] - 1] == ' ' || src[mas[1] - 1] == '\t'))
				dst[mas[0]++] = ' ';
		}
		else
			dst[mas[0]++] = src[mas[1]];
	}
	free(src);
	return (dst);
}

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
