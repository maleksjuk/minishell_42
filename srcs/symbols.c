/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:45:19 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/13 13:10:38 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*ft_strtrim_into(char *src)
{
	char	*dst;
	int		i;

	if (!(dst = ft_strnew(ft_strlen(src) + 1)))
		return (NULL);
	i = 0;
	while (*src)
	{
		if (*src == ' ' || *src == '\t')
		{
			if (!(*(src - 1) == ' ' || *(src - 1) == '\t'))
				dst[i++] = ' ';
		}
		else
			dst[i++] = *src;
		src++;
	}
	return (dst);
}

char	*check_symbols(char *cmd, char **env)
{
	char	*str;
	char	*tmp;

	str = ft_strtrim(cmd);
	tmp = str;
	str = ft_strtrim_into(str);
	if (!str)
		return (NULL);
	free(tmp);
	printf("check_symbols(): trim = |%s|; ", str);
	if (ft_strchr(str, '~'))
	{
		tmp = str;
		str = sml_tilda(str, env);
		printf("tilda = |%s|; ", str);
		if (!str)
			return (NULL);
		free(tmp);
	}
	if (ft_strchr(str, '$'))
	{
		tmp = str;
		str = sml_dollar(str, env);
		printf("dollar = |%s|", str);
		if (!str)
			return (NULL);
		free(tmp);
	}
	printf("\n");
	return (str);
}
