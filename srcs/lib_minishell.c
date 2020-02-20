/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 09:57:50 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/20 11:24:49 by obanshee         ###   ########.fr       */
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
	// char	*str;
	int		i;

	i = -1;
	while (env[++i])
		if (ft_strnequ(env[i], name, ft_strlen(name)))
			break ;
	// str = ft_strjoin(name, var);
	free(env[i]);
	env[i] = ft_strjoin(name, var);
	return (env);
}
