/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:55:56 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/22 17:08:26 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*get_from_wait_quotes(int quote[2])
{
	char	*bufer;
	char	*continue_cmd;
	
	if (quote[0])
		ft_printf("quote> ");
	else if (quote[1])
		ft_printf("dquote> ");
	bufer = get_cmd(0);
	continue_cmd = check_quote_in_cmd(bufer, quote);
	return (continue_cmd);
}

char	*get_tilda(t_env *env, char *str, int *i)
{
    char	*tmp;

	tmp = NULL;
	if (!str)
		return (0);
	if (str[1] == '+')
		tmp = value_from_env(env, "PWD");
	else if (str[1] == '-')
		tmp = value_from_env(env, "OLDPWD");
	else if (!str[1] || str[1] == '/' || str[1] == ' ' || str[1] == ';')
		tmp = value_from_env(env, "HOME");
	else if (ft_isalpha(str[1]))
	{
		tmp = users_tilda(&str[1], env);
		if (!tmp)
			return (0);
	}
	if (!tmp)
		return (1);
	ft_strncpy(str, tmp, ft_strlen(tmp));
	return (prepate_to_return(tmp, str));
	return ;
}

char	*get_dollar(int *i)
{
	return ;
}

char	*replace_symbols(char *str, char (*func)(int *), char smbl, int *i)
{
	char	*to_replace;
	char	*new_str;
	int		index;

	while (str[index])
		index++;
	str[index - 1] = smbl;
	to_replace = func(*i);
	new_str = ft_strjoin(str, to_replace);
	free(str);
	return (new_str);
}

void	init_quote(int quote[2], int quote_rec[2])
{
	if (quote_rec)
	{
		quote[0] = quote_rec[0];
		quote[1] = quote_rec[1];
	}
	else
	{
		quote[0] = 0;
		quote[1] = 0;
	}
}

void	*check_quote_position(char *cmd, char *str, int i, int quote[2])
{
	if (cmd[i] == '\'' && !quote[1])
	{
		quote[0] = !quote[0];
		str[i] = '"';
	}
	else if (cmd[i] == '"' && !quote[0])
	{
		quote[1] = !quote[1];
		str[i] = '"';
	}
	else
		str[i] = cmd[i];
}

char	*check_quotes(char *cmd, int quote_rec[2])
{
	char	*str;
	int		i;
	int		quote[2];

	init_quote(quote, quote_rec);
	str = ft_strnew(ft_strlen(cmd) + 1);
	i = 0;
	while (cmd[i])
	{
		check_quote_position(cmd, str, i, quote);

		// CHECK CONTENT
		if (str[i] == '~' && !quote[0] && !quote[1])
			str = replace_symbols(str, get_tilda, '\0', &i);
		else if (str[i] == '$' && !quote[0] && str[i + 1] &&
			!ft_isspace(str[i + 1]))
			str = replace_symbols(str, get_dollar, '\0', &i);

		i++;
	}

	// CHECK END INPUT
	if (quote[0] || quote[1])
		if (!quote_rec) // CHANGE CONDITION
			str = replace_symbols(str, get_from_wait_quotes, '\n', quote);

	return (str);
}
