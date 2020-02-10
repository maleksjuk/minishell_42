/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:45:19 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/10 12:57:26 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*users_tilda(char *cmd, char **env)
{
	int		i;
	char	*user;
	char	*home;

	home = var_from_env(env, "HOME");
	i = ft_strlen(home);
	while (home[--i] != '/')
		home[i] = '\0';
	i = -1;
	while (cmd[++i])
		if (cmd[i] == ' ')
			break ;
	user = ft_strjoin_len(home, cmd, i, ft_strlen(home));
	if (access(user, F_OK))
	{
		error_message("no such file", user);
		return (NULL);
	}
	return (user);
}

int		sml_tilda_check(char *cmd, char *str, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (cmd[1] == '+')
		tmp = var_from_env(env, "PWD");
	else if (cmd[1] == '-')
		tmp = var_from_env(env, "OLDPWD");
	else if (!cmd[1] || cmd[1] == '/' || cmd[1] == ' ' || cmd[1] == ';')
		tmp = var_from_env(env, "HOME");
	else if (ft_isalpha(cmd[1]))
	{
		tmp = users_tilda(&cmd[1], env);
		if (!tmp)
			return (0);
	}
	if (!tmp)
		return (1);
	if (cmd[1] == '+' || cmd[1] == '-' || ft_isalpha(cmd[1]))
		while (cmd[i] && cmd[i] != ' ')
			i++;
	ft_strncpy(str, tmp, ft_strlen(tmp));
	return (ft_strlen(tmp) + i);
}

char	*sml_tilda(char *cmd, char **env)
{
	char	*str;
	int		i;
	int		j;
	int		quote;
	int		len;

	str = ft_strnew(LEN_PATH * 2);
	i = 0;
	j = 0;
	quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
		{
			if (!quote)
				quote = 1;
			else
				quote = 0;
		}
		if (cmd[i] == '~' && !quote)
		{
			len = sml_tilda_check(&cmd[i], &str[j], env);
			if (!len)
				return (NULL);
			j += len - 1;
		}
		else
			str[j] = cmd[i];
		i++;
		j++;
	}
	return (str);
}

int		sml_dollar_check(char *cmd, char *str, char **env)
{
	int		i;
	char	*tmp;
	char	*name;

	i = 1;
	tmp = NULL;
	while (ft_isalnum(cmd[i]) || cmd[i] == '_')
		i++;
	name = ft_strnew(i);
	ft_strncpy(name, cmd + 1, i - 1);
	tmp = var_from_env(env, name);
	if (!tmp)
		return (-1);
	ft_strncpy(str, tmp, ft_strlen(tmp));
	return (ft_strlen(tmp));
}

char	*sml_dollar(char *cmd, char **env)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	str = ft_strnew(LEN_PATH * 2);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			len = sml_dollar_check(&cmd[i], &str[j], env);
			if (!len)
				return (NULL);
			else if (len != -1)
				j += len - 1;
			else
				j--;
			i++;
			while (ft_isalnum(cmd[i]) || cmd[i] == '_')
				i++;
			i--;
		}
		else
			str[j] = cmd[i];
		i++;
		j++;
	}
	return (str);
}

char	*check_symbols(char *cmd, char **env)
{
	char	*str;
	char	*tmp;

	str = sml_tilda(cmd, env);
	if (!str)
		return (NULL);
	tmp = str;
	str = sml_dollar(str, env);
	if (!str)
		return (NULL);
	free(tmp);
	return (str);
}
