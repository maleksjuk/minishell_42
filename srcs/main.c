/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/24 20:01:29 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int proccess(char *cmd)
{
    ft_printf("%s", cmd);
    return (0);
}

int main(void)
{
	int		count;
	char	*bufer;

	count = 1024;
	while (1)
	{
		ft_printf("$> ");
		bufer = ft_strnew(count);
		read(0, bufer, count);
		if (ft_strequ(bufer, "exit"))
			exit(0);
		proccess(bufer);
        free(bufer);
	}
	return (0);
}
