/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:53:05 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/30 12:57:16 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libftprintf/includes/ft_printf.h"
# include "../libftprintf/includes/get_next_line.h"
# include "../libftprintf/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>

# define LEN_PATH 1024

/*
**	main.c
*/
char	**get_env(char **envp);

/*
**	lib_minishell.c
*/
char	**set_array_2(int len);

/*
**  commands.c
*/
int	    cmd_echo(char *str);
int	    cmd_cd(char *path);
int	    cmd_pwd(void);
int	    cmd_env(char **env);
char	**cmd_setenv(char *str, char **env);
char	**cmd_unsetenv(char *name, char **env);

/*
**  cmd_exe.c
*/
int	    cmd_more(char *cmd, char **env);

#endif