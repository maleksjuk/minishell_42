/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sml_tilda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:01:24 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/28 10:22:26 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*users_tilda(char *cmd, char **env)
{
	int		i;
	char	*user;
	char	*home;

	home = var_from_env(env, "HOME");
	i = ft_strlen(home) - 1;
	while (home[i] && home[i] != '/')
		home[i--] = '\0';
	i = -1;
	while (cmd[++i])
		if (cmd[i] == ' ')
			break ;
	user = ft_strjoin_len(home, cmd, i, ft_strlen(home));
	free(home);
	if (access(user, F_OK))
	{
		error_message("no such file", user);
		free(user);
		return (NULL);
	}
	return (user);
}

int		prepate_to_return(char *tmp, char *cmd)
{
	int		i;

	i = 0;
	if (cmd[1] == '+' || cmd[1] == '-' || ft_isalpha(cmd[1]))
		while (cmd[i] && cmd[i] != ' ')
			i++;
	i += ft_strlen(tmp);
	free(tmp);
	return (i);
}
//	check
int		sml_tilda_check(char *cmd, char *str, char **env)
{
	char	*tmp;

	tmp = NULL;
	if (!cmd)
		return (0);
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
	ft_strncpy(str, tmp, ft_strlen(tmp));	//check
	return (prepate_to_return(tmp, cmd));
}

int		helper_tilda(char c, int *quote, char *cmd, int i)
{
	if (c == '"')
	{
		if (*quote)
			*quote = 0;
		else
			*quote = 1;
	}
	if (cmd[i] == '~' && !(*quote) && ((i > 0 && cmd[i - 1] == ' ') || i == 0)
		&& cmd[i + 1] != '~')
		return (1);
	return (0);
}

char	*sml_tilda(char *cmd, char **env)
{
	char	*str;
	int		i;
	int		j;
	int		quote;
	int		len;

	str = ft_strnew(LEN_PATH * 2);
	i = -1;
	j = 0;
	quote = 0;
	while (cmd[++i])
	{
		if (helper_tilda(cmd[i], &quote, cmd, i))
		{
			len = sml_tilda_check(&cmd[i], &str[j], env);
			if (!len)
				return (NULL);
			j += len - 1;
		}
		else
			str[j] = cmd[i];
		j++;
	}
	return (str);
}
