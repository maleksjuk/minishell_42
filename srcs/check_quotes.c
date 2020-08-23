/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:55:56 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/23 15:44:45 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*get_from_wait_quotes(t_env *env, int quote[2])
{
	char	*bufer;
	char	*continue_cmd;
	
	if (quote[0])
		ft_printf("quote> ");
	else if (quote[1])
		ft_printf("dquote> ");
	bufer = get_cmd(0);
	continue_cmd = check_quotes(env, bufer, quote);
	return (continue_cmd);
}

char	*replace_symbols(char *str, char *(*func)(t_env *, char *, int *), 
						int *i, t_env *env)
{
	char	*to_replace;
	char	*new_str;

	to_replace = func(env, str, i);
	if (!to_replace)
		return (str);
	new_str = ft_strjoin(str, to_replace);
	free(str);
	free(to_replace);
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

void	check_quote_position(char *cmd, char *str, int i, int quote[2])
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
	else if (cmd[i] != '~' && cmd[i] != '$')
		str[i] = cmd[i];
}

char	*check_quotes(t_env *env, char *cmd, int quote_rec[2])
{
	char	*str;
	int		i;
	int		quote[2];
	char	*to_replace;
	char	*new_str;

	init_quote(quote, quote_rec);
	str = ft_strnew(ft_strlen(cmd) + 1);
	i = -1;
	while (cmd[++i])
	{
		check_quote_position(cmd, str, i, quote);

		// CHECK CONTENT
		if (cmd[i] == '~' && !quote[0] && !quote[1])
			str = replace_symbols(cmd, get_tilda, &i, env);
		else if (cmd[i] == '$' && !quote[0] && str[i + 1] &&
			!ft_isspace(cmd[i + 1]))
			str = replace_symbols(cmd, get_dollar, &i, env);
	}

	// CHECK END INPUT
	if (quote[0] || quote[1])
		if (!quote_rec) // CHANGE CONDITION
		{
			str[i++] = '\n';
			to_replace = get_from_wait_quotes(env, quote);
			new_str = ft_strjoin(str, to_replace);
			free(str);
			free(to_replace);
			str = new_str;
		}

	return (str);
}
