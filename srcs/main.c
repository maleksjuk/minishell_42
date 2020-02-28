/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/28 11:20:24 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int argc, char **argv, char **envp)
{
	char	*bufer;
	char	**env;

	env = get_env(envp);
	if (!env)
		return (error_message("error", "null env"));
	ft_printf("* * * MINISHELL [begin] * * *\n");
	while (1)
	{
		ft_printf("---minishell$ ");
		bufer = ft_strnew(LEN_PATH);
		get_next_line(0, &bufer);
		if (!ft_strequ(bufer, ""))
		{
			if (ft_strequ(bufer, "exit") || (ft_strnequ(bufer, "exit", 4) &&
				ft_strlen(bufer) > 4 && bufer[4] == ' '))
				cmd_exit(env, bufer);
			check_cmd(bufer, &env);
		}
		free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
