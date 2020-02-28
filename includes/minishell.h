/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:53:05 by obanshee          #+#    #+#             */
/*   Updated: 2020/02/28 11:25:38 by obanshee         ###   ########.fr       */
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
**	main_functions.c 5	check cmd_more
*/
int	    error_message(char *str, char *file);
int	    cmd_more(char *cmd, char **env);
int		check_cmd(char *cmd, char ***env);
char	**get_env(char **envp);
void	cmd_exit(char **env, char *bufer);

/*
**	lib_minishell.c 5	ok
*/
char	**set_array_2(int len);
char	*var_from_env(char **env, char *name);
char	**var_to_env(char **env, char *name, char *var);
char	*ft_strtrim_into(char *cmd);
char	*path_program_from_env(char *prgm, char **path_array);

/*
**  cmd_base.c 5	check cmd_unsetenv
*/
int	    cmd_echo(char *str);
int	    cmd_pwd(void);
int	    cmd_env(char **env);
char	**cmd_setenv(char *str, char **env);
char	**cmd_unsetenv(char *name, char **env);

/*
**  cmd_cd.c 3		ok
*/
char    **cmd_cd(char ***env, char *path);

/*
**  cmd_more.c 5	ok
*/
char	*cmd_program(char *prgm, char **env);
char	**cmd_arguments(char *cmd);
int		cmd_system(char *prgm, char **argv, char **env);

/*
**  symbols.c 4     ok
*/
char	*sml_dollar(char *cmd, char **env);
char    *check_symbols(char *cmd, char **env);

/*
**  sml_tilda.c 5	check sml_tilda_check
*/
char	*sml_tilda(char *cmd, char **env);

#endif