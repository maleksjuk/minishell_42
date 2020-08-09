/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:45:19 by obanshee          #+#    #+#             */
/*   Updated: 2020/03/07 12:05:50 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		sml_dollar_check(char *cmd, char *str, t_env *env)
{
	int		i;
	char	*value;
	char	*name;

	i = 1;
	while (ft_isalnum(cmd[i]) || cmd[i] == '_')
		i++;
	name = ft_strnew(i);
	ft_strncpy(name, cmd + 1, i - 1);
	value = value_from_env(env, name);
	if (!value)
		return (-1);
	ft_strncpy(str, value, ft_strlen(value));
	i = ft_strlen(value);
	free(name);
	free(value);
	return (i);
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

char	*sml_dollar(char *cmd, t_env *env, int nbr)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	str = ft_strnew(ft_strlen(cmd) + LEN_PATH * (nbr + 1) + 1);
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

int		nbr_sml(char *str, char c)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (*str == c)
			len++;
		str++;
	}
	return (len);
}

char	*get_full_cmd(char *cmd, t_env *env)
{
	char	*str;
	char	*new_str;

	str = ft_strtrim_into(cmd);
	if (!str)
		return (NULL);
	if (ft_strchr(str, '~'))
	{
		new_str = sml_tilda(str, env, nbr_sml(str, '~'));
		if (!new_str)
			return (NULL);
		free(str);
		str = new_str;
	}
	if (ft_strchr(str, '$'))
	{
		new_str = sml_dollar(str, env, nbr_sml(str, '$'));
		if (!new_str)
			return (NULL);
		free(str);
		str = new_str;
	}
	return (str);
}
