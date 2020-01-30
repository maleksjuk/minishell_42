/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_more.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:35:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/30 12:59:25 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_program(char *cmd)
{
	char	*str;
	int		i;
	int		ins;

	ins = 5;
	if (ft_strnequ(cmd, "/bin/", 5))
		ins = 0;
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	str = ft_strnew(i + 1 + ins);
	ft_strncpy(str, "/bin/", ins);
	ft_strncpy(str + ins, cmd, i);
	str[i + ins] = '\0';
	return (str);
}

char	**cmd_arguments(char *cmd)
{
	char	**arguments;

	arguments = ft_strsplit(cmd, ' ');
	return (arguments);
}

int	cmd_system(char *prgm, char **argv, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		execve(prgm, argv, env);
		exit(-1);
	}
	if (waitpid(pid, &status, 0))
		return (-1);
	else if (WIFEXITED(status))
		return (WIFEXITED(status));
	return (-1);
}

int	cmd_more(char *cmd, char **env)
{

	char	*prgm;
	char	**argv;
	// int		i;

	// ft_printf("\tEXE: input: %s\n", cmd);
	prgm = cmd_program(cmd);
	// ft_printf("\tEXE: program: %s\n", prgm);
	argv = cmd_arguments(cmd);
	// if (!argv)
	// 	ft_printf("\tEXE: arguments: NULL\n");
	// else
	// {
	// 	i = -1;
	// 	while (argv[++i])
	// 		ft_printf("\tEXE: agruments[%i]: %s\n", i, argv[i]);
	// }
	cmd_system(prgm, argv, env);
	return (0);
}
