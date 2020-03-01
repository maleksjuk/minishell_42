/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:58:38 by obanshee          #+#    #+#             */
/*   Updated: 2020/03/01 13:41:44 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_input_setenv(char *str)
{
	int		space;
	int		equal;
	int		quote;
	int		i;

	i = -1;
	quote = 0;
	space = 0;
	equal = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			quote = quote ? 0 : 1;
		if (!quote && str[i] == ' ')
			space++;
		if (!quote && str[i] == '=')
			equal++;
	}
	if (!((equal && !space) || (space && !equal)))
		error_message("setenv", "error numbers of arguments");
	else
		return (0);
	return (1);
}

char	*get_key_from_str(char *str)
{
	char	*key;
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ' || str[i] == '=')
			break ;
	key = ft_strnew(i + 1);
	ft_strncpy(key, str, i);
	return (key);
}

char	**rewrite_var_env(char **env, int num, char *str)
{
	char	*new_var;
	int		i;

	new_var = ft_strdup(str);
	if (!ft_strchr(new_var, '='))
	{
		i = 0;
		while (new_var[i] != ' ')
			i++;
		new_var[i] = '=';
	}
	free(env[num]);
	env[num] = new_var;
	return (env);
}

char	**new_array_env(char **env, int i, char *str)
{
	char	**env_new;
	int		j;

	if (!(env_new = set_array_2(i + 1)))
		return (env);
	i = -1;
	while (env[++i] && !ft_strequ(env[i], ""))
	{
		env_new[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	env_new[i] = ft_strdup(str);
	if (!ft_strchr(env_new[i], '='))
	{
		j = 0;
		while (env_new[i][j] != ' ')
			j++;
		env_new[i][j] = '=';
	}
	return (env_new);
}

char	**cmd_setenv(char *str, char **env)
{
	char	**env_new;
	int		i;
	char	*key;
	int		flag;

	if (!env)
		return (NULL);
	if (check_input_setenv(str))
		return (env);
	key = get_key_from_str(str);
	i = -1;
	flag = 0;
	while (env[++i])
		if (ft_strnequ(env[i], key, ft_strlen(key)))
		{
			flag = 1;
			break ;
		}
	if (flag)
		env_new = rewrite_var_env(env, i, str);
	else
		env_new = new_array_env(env, i, str);
	return (env_new);
}
