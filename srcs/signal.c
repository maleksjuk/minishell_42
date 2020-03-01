/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:48:07 by obanshee          #+#    #+#             */
/*   Updated: 2020/03/01 12:00:32 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    cmd_listener(int sig)
{
    if (sig == SIGINT)
        ft_printf("\n");
}

void    main_listener(int sig)
{
    if (sig == SIGINT)
        ft_printf("\n---minishell$ ");
}
