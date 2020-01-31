/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:45:19 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/31 12:44:46 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*home_from_env(char **env)
{
	char	*home;
	int		i;

	i = -1;
	while (env[++i])
		if (ft_strnequ(env[i], "HOME", 4))
			break ;
	home = ft_strdup(env[i] + 5);
	return (home);
}

char	*sml_tilda(char *cmd, char *home)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strnew(LEN_PATH * 2);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '~')
		{
			ft_strncpy(&str[j], home, ft_strlen(home));
			j += ft_strlen(home) - 1;
		}
		else
			str[j] = cmd[i];
		i++;
		j++;
	}
	return (str);
}

char	*sml_dollar(char *cmd)
{
	return(cmd);
}

char	*check_symbols(char *cmd, char **env)
{
	char	*str;
	char	*home;
	char	*tmp;

	home = home_from_env(env);
	str = sml_tilda(cmd, home);
	tmp = str;
	str = sml_dollar(str);
	free(tmp);
	return (str);
}
