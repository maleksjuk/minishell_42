/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/22 14:16:20 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_exit(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (ft_strnequ(str, "exit", 4));
}

void	cmd_input(char *bufer, t_env *env, int *exit_flag)
{
	char	**cmd_list;
	int		i;

	cmd_list = ft_strsplit(bufer, ';');
	i = 0;
	while (cmd_list[i])
	{
		if (!*exit_flag && check_exit(cmd_list[i]))
			*exit_flag = 1;
		if (!*exit_flag)
			cmd_processing(cmd_list[i], env);
		free(cmd_list[i]);
		i++;
	}
	free(cmd_list);
}

char	*get_cmd(int fd)
{
	char	*bufer;
	int		buf_size;
	char	*smbl;
	int		i;

	buf_size = 1024;
	bufer = ft_strnew(buf_size);
	smbl = ft_strnew(1);
	i = 0;
	while (read(fd, smbl, 1) > 0)
	{
		if (*smbl == '\n')
			break ;
		bufer[i] = *smbl;
		i++;
	}
	free(smbl);
	return (bufer);
}

int		main(int argc, char **argv, char **envp)
{
	char	*bufer;
	t_env	*env;
	int		exit_flag;

	exit_flag = 0;
	env = get_env(envp);
	if (!env)
		return (error_message("error", "null env"));
	ft_printf("\033[1;7;32m* * * MINISHELL [start] * * *\033[0m\n");
	while (1)
	{
		signal(SIGINT, main_listener);
		ft_printf("\033[1;34m---minishell$ \033[0m");
		bufer = get_cmd(0);
		if (!ft_strequ(bufer, ""))
			cmd_input(bufer, env, &exit_flag);
		free(bufer);
		if (exit_flag)
			cmd_exit(env);
	}
	return (0);
	(void)argc;
	(void)argv;
}
