/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:55:56 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/29 17:15:53 by obanshee         ###   ########.fr       */
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
		ft_printf("\033[31mquote> \033[0m");
	else if (quote[1])
		ft_printf("\033[31mdquote> \033[0m");
	bufer = get_cmd(0);
	continue_cmd = check_quotes(env, bufer, quote);
	free(bufer);
	return (continue_cmd);
}

char	*replace_symbols(char *str, char *to_replace, int *i)
{
	char	*new_str;
	char	*new_space;

	new_str = ft_strjoin(str, to_replace);
	free(str);
	str = new_str;
	new_space = ft_strnew(LEN_PATH);
	new_str = ft_strjoin(str, new_space);
	free(str);
	*i += ft_strlen(to_replace) - 1;
	return (new_str);
}

void	init_quote(int *quote, int *quote_rec)
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

void	check_quote_position(char *cmd, char *str, int *i, int quote[2])
{
	int	flag;

	flag = 0;
	if (cmd[i[0]] == '\'' && quote[1] == 0)
	{
		quote[0] = !quote[0];
		flag = 1;
	}
	else if (cmd[i[0]] == '"' && quote[0] == 0)
	{
		quote[1] = !quote[1];
		flag = 1;
	}
	if (cmd[i[0]] != '~' && cmd[i[0]] != '$' && !flag)
		str[i[1]] = cmd[i[0]];
	if (flag)
		i[1]--;
}

char	*check_quotes(t_env *env, char *cmd, int quote_rec[2])
{
	char	*str;
	int		i[2];		// 0 - cmd. 1 - str
	int		quote[2];	// 0 - once, 1 - twice
	char	*to_replace;
	char	*new_str;

	init_quote(quote, quote_rec);
	str = ft_strnew(ft_strlen(cmd) + 1);
	i[0] = -1;
	i[1] = -1;
	to_replace = NULL;
	while (cmd[++i[0]])
	{
		i[1]++;
		check_quote_position(cmd, str, i, quote);

		// CHECK CONTENT
		if (cmd[i[0]] == '~' && !quote[0] && !quote[1] && 
			ft_isspace(cmd[i[0] - 1]))
			to_replace = get_tilda(env, &cmd[i[0]]);
		else if (cmd[i[0]] == '$' && !quote[0] && cmd[i[0] + 1] &&
			!ft_isspace(cmd[i[0] + 1]))
			to_replace = get_dollar(env, &cmd[i[0]]);
		else if (cmd[i[0]] == '~' || cmd[i[0]] == '$')
			str[i[1]] = cmd[i[0]];
		
		if (to_replace)
		{
			str = replace_symbols(str, to_replace, &i[1]);
			free(to_replace);
			to_replace = NULL;
			while (cmd[i[0]] && cmd[i[0]] != ' ' && cmd[i[0]] != '"') // check
				i[0]++;
			// while (cmd[i[0]] && ft_isalnum(cmd[i[0]]))
			// 	i[0]++;
			i[0]--;
		}
	}

	// CHECK END INPUT
	if (quote[0] || quote[1])
	{
		str[++i[1]] = '\n';
		to_replace = get_from_wait_quotes(env, quote);
		new_str = ft_strjoin(str, to_replace);
		free(str);
		free(to_replace);
		str = new_str;
	}

	return (str);
}
