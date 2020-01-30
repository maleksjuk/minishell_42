/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:35:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/30 11:12:55 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_program(char *cmd)
{
	char	*str;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	ft_strncpy(str, cmd, i);
	str[i] = '\0';
	return (str);
}

char	**cmd_arguments(char *cmd, char *prgm)
{
	char	**arguments;
	int		i;
	int		count;

	count = 0;
	i = ft_strlen(prgm) - 1;
	while (cmd[++i])
		if (cmd[i] == ' ')
			count++;
	if (count == 0)
		return (NULL);
	arguments = ft_strsplit(cmd + ft_strlen(prgm), ' ');
	return (arguments);
}

int	cmd_other(char *cmd, char **env)
{
	pid_t	exe;
	char	*prgm;
	char	**argv;
	int		i;

	ft_printf("\tinput: %s\n", cmd);
	prgm = cmd_program(cmd);
	ft_printf("\tprogram: %s\n", prgm);
	argv = cmd_arguments(cmd, prgm);
	if (!argv)
		ft_printf("\targuments: NULL\n");
	else
	{
		i = -1;
		while (argv[++i])
			ft_printf("\tagruments[%i]: %s\n", i, argv[i]);
	}
	exe = fork();
	if (!exe)
	{
		ft_printf("\tpid = 0; I'm proccess-child\n");
		if (execve(cmd, argv, env) == -1)
			ft_printf("\terrno = %i\n", errno);
	}
	else
	{
		ft_printf("\tpid = %d; I'm proccess-parent\n", exe);
	}
	return (0);
}
