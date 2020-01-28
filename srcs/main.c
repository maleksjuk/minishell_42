/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/28 12:34:19 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	proccess(char *cmd)
{
	ft_printf("%s", cmd);
	// if (execve(cmd, NULL, NULL) == -1)
	// 	ft_printf("errno = %i\n", errno);
	return (0);
}

int	check_cmd(char *str, char **envp)
{
	if (ft_strnequ(str, "echo", 4))
		return (cmd_echo(str + 5));
	else if (ft_strnequ(str, "cd", 2))
		return (cmd_cd(str + 3));
	else if (ft_strequ(str, "pwd"))
		return (cmd_pwd());
	else if (ft_strequ(str, "env"))
		return (cmd_env(envp));
	else
		return (proccess(str));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*bufer;

	while (1)
	{
		ft_printf("$> ");
		bufer = ft_strnew(LEN_PATH);
		// read(0, bufer, count);
		get_next_line(0, &bufer);
		if (ft_strnequ(bufer, "exit", 4))
			exit(0);
		check_cmd(bufer, envp);
		free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
