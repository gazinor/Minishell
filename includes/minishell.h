/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 04:15:01 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/14 07:49:43 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include "../srcs/gnl/get_next_line.h"
# include "../srcs/printf/ft_printf.h"

struct dirent		*readdir(DIR *dir);

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_data
{
	char			*here;
	t_env			*env;
	int				pid;
	char			**paths;
	char			**option;
	char			*exec;
	char			*binary;
}					t_data;

char				**ft_split(const char *s, char c);
void				ft_pwd(char *line);
int					is_builtin(char *str, t_data *data);
void				init_env(t_env **env, char **envp);
char				*where_am_i(void);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, int n);
int					check_char(char *str, char c);
char				**get_paths(t_data *data);
char				*find_key_value(t_env *env, char *key);
char				**ft_split_env(t_env *env);
void				ft_export(char *str, t_env **env, t_data *data);
void				add_new_elem(t_env **env, char *key, char *value);
void				ft_unset(char *str, t_data *data);

#endif
