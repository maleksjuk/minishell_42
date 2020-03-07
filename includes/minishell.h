/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:53:05 by obanshee          #+#    #+#             */
/*   Updated: 2020/03/07 12:45:32 by obanshee         ###   ########.fr       */
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
# include <signal.h>

# define LEN_PATH 1024

/*
**	main_functions.c
*/
int		error_message(char *str, char *file);
int		cmd_more(char *cmd, char **env);
int		check_cmd(char *cmd, char ***env);
char	**get_env(char **envp);
void	cmd_exit(char **env, char *bufer);

/*
**	lib_minishell.c
*/
char	**set_array_2(int len);
char	*var_from_env(char **env, char *name);
char	**var_to_env(char **env, char *name, char *var);
char	*ft_strtrim_into(char *cmd);
char	*path_program_from_env(char *prgm, char **path_array);

/*
**  cmd_base.c
*/
int		cmd_echo(char *str);
int		cmd_pwd(void);
int		cmd_env(char **env);
char	**cmd_unsetenv(char *name, char **env);

/*
**  cmd_setenv.c
*/
char	**cmd_setenv(char *str, char **env);

/*
**  cmd_cd.c
*/
char	**cmd_cd(char ***env, char *path);

/*
**  cmd_more.c
*/
char	*cmd_program(char *prgm, char **env);
char	**cmd_arguments(char *cmd);
int		cmd_system(char *prgm, char **argv, char **env);

/*
**  symbols.c
*/
char	*sml_dollar(char *cmd, char **env, int nbr);
char	*check_symbols(char *cmd, char **env);

/*
**  sml_tilda.c
*/
char	*sml_tilda(char *cmd, char **env, int nbr);

/*
**  signal.c
*/
void	cmd_listener(int sig);
void	main_listener(int sig);

#endif
