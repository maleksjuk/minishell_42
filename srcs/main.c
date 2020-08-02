/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/03/07 11:59:01 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	separator(char *bufer, t_env *env)
{
	char	**cmd_list;
	int		i;

	cmd_list = ft_strsplit(bufer, ';');
	i = -1;
	while (cmd_list[++i])
	{
		check_cmd(cmd_list[i], env);
		free(cmd_list[i]);
	}
	free(cmd_list);
}

int		main(int argc, char **argv, char **envp)
{
	char	*bufer;
	t_env	*env;

	env = get_env(envp);
	if (!env)
		return (error_message("error", "null env"));
	ft_printf("\033[1;7;32m* * * MINISHELL [start] * * *\033[0m\n");
	while (1)
	{
		signal(SIGINT, main_listener);
		ft_printf("\e[1;34m---minishell$ \e[0m");
		get_next_line(0, &bufer);
		if (!ft_strequ(bufer, ""))
		{
			if (ft_strequ(bufer, "exit") || (ft_strnequ(bufer, "exit", 4) &&
				ft_strlen(bufer) > 4 && bufer[4] == ' '))
				cmd_exit(env, bufer);
			separator(bufer, env);
		}
		free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
