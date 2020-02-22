/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:45:19 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/22 16:26:00 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		sml_dollar_check(char *cmd, char *str, char **env)
{
	int		i;
	char	*tmp;
	char	*name;

	i = 1;
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

void	helper_dollar(char *cmd, int *i, int *j, int len)
{
	if (len != -1)
		*j += len - 1;
	else
		(*j)--;
	(*i)++;
	while (ft_isalnum(cmd[*i]) || cmd[*i] == '_')
		(*i)++;
	(*i)--;
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
			helper_dollar(cmd, &i, &j, len);
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

	str = ft_strtrim_into(cmd);
	if (!str)
		return (NULL);
	if (ft_strchr(str, '~'))
	{
		tmp = str;
		str = sml_tilda(str, env);
		if (!str)
			return (NULL);
		free(tmp);
	}
	if (ft_strchr(str, '$'))
	{
		tmp = str;
		str = sml_dollar(str, env);
		if (!str)
			return (NULL);
		free(tmp);
	}
	return (str);
}
