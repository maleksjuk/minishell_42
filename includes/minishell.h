/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:53:05 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/20 11:30:16 by obanshee         ###   ########.fr       */
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
int	    error_message(char *str, char *file);
char	**get_env(char **envp);

/*
**	lib_minishell.c
*/
char	**set_array_2(int len);
char	*var_from_env(char **env, char *name);
char	**var_to_env(char **env, char *name, char *var);

/*
**  cmd_base.c
*/
int	    cmd_echo(char *str);
char    **cmd_cd(char ***env, char *path);
int	    cmd_pwd(void);
int	    cmd_env(char **env);
char	**cmd_setenv(char *str, char **env);
char	**cmd_unsetenv(char *name, char **env);

/*
**  cmd_more.c
*/
int	    cmd_more(char *cmd, char **env);

/*
**  symbols.c
*/
char    *check_symbols(char *cmd, char **env);

/*
**  sml_tilda.c
*/
char	*users_tilda(char *cmd, char **env);
int		sml_tilda_check(char *cmd, char *str, char **env);
char	*sml_tilda(char *cmd, char **env);

#endif