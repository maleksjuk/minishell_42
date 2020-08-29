/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilda_or_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 14:53:19 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/29 13:04:48 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*users_tilda(char *str, t_env *env)
{
	int		i;
	char	*user;
	char	*home;

	home = value_from_env(env, "HOME");
	i = ft_strlen(home) - 1;
	while (home[i] && home[i] != '/')
		home[i--] = '\0';
	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			break ;
	user = ft_strjoin_len(home, str, i, ft_strlen(home));
	free(home);
	if (access(user, F_OK))
	{
		error_message("no such file", user);
		free(user);
		return (NULL);
	}
	return (user);
}

char	*get_tilda(t_env *env, char *str, int *i)
{
	char	*to_add;

	ft_printf("TILDA\n");

	if (!str)
		return (NULL);
	if (str[*i + 1] == '+')
		to_add = value_from_env(env, "PWD");
	else if (str[*i + 1] == '-')
		to_add = value_from_env(env, "OLDPWD");
	else if (!str[*i + 1] || str[*i + 1] == '/' || str[*i + 1] == ' ' || 
			str[*i + 1] == ';')
		to_add = value_from_env(env, "HOME");
	else if (ft_isalpha(str[*i + 1]))
		to_add = users_tilda(&str[*i + 1], env);
	else
		to_add = ft_strdup("~");
	if (!to_add)
		return (NULL);
	*i += ft_strlen(to_add);
	return (to_add);
}

char	*get_dollar(t_env *env, char *str)
{
	int		len;
	char	*key;
	char	*to_add;

	ft_printf("DOLLAR\n");

	len = 1;
	while (ft_isalnum(str[len]))
		len++;
	key = ft_strnew(len + 1);
	if (!key)
		return (NULL);
	ft_strncpy(key, &str[1], len);
	to_add = value_from_env(env, key);
	free(key);
	if (!to_add)
		return (NULL);
	return (to_add);
}
