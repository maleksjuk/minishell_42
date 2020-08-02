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

typedef struct	s_env
{
	char			*key;
	char			*value;
	char			*str;
	struct s_env	*next;
}				t_env;

/*
**	main_functions.c
*/
int		error_message(char *str, char *file);
int		cmd_more(char *cmd, t_env *env);
int		check_cmd(char *cmd, t_env *env);
t_env	*get_env(char **envp);
void	cmd_exit(t_env *env, char *bufer);
t_env	*create_one_env(char *str);

/*
**	lib_minishell.c
*/
char	**set_array_2(int len);
char	*value_from_env(t_env *env, char *name);
char	**var_to_env(char **env, char *name, char *var);
char	*ft_strtrim_into(char *cmd);
char	*path_program_from_env(char *prgm, char **path_array);

/*
**  cmd_base.c
*/
int		cmd_echo(char *str);
int		cmd_pwd(void);
int		cmd_env(t_env *env);
void	cmd_unsetenv(char *name, t_env *env);

/*
**  cmd_setenv.c
*/
void	cmd_setenv(char *str, t_env *env);

/*
**  cmd_cd.c
*/
void	cmd_cd(t_env *env, char *path);

/*
**  cmd_more.c
*/
char	*cmd_program(char *prgm, char *path_env);
char	**cmd_arguments(char *cmd);
int		cmd_system(char *prgm, char **argv, t_env *env);

/*
**  symbols.c
*/
char	*sml_dollar(char *cmd, t_env *env, int nbr);
char	*check_symbols(char *cmd, t_env *env);

/*
**  sml_tilda.c
*/
char	*sml_tilda(char *cmd, t_env *env, int nbr);

/*
**  signal.c
*/
void	cmd_listener(int sig);
void	main_listener(int sig);

#endif
