/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 09:57:50 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/30 09:58:03 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_array_2(int len)
{
	char	**array;
	int		i;

	if (!(array = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	i = 0;
	while (i < len)
		array[i++] = NULL;
	return (array);
}
