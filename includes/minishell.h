/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:06:18 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/02 19:33:02 by glaurent         ###   ########.fr       */
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
# include <sys/types.h>
# include <fcntl.h>
# include "../srcs/gnl/get_next_line.h"
# include "../srcs/printf/ft_printf.h"

struct dirent		*readdir(DIR *dir);

typedef struct		s_file
{
	char			*filename;
	int				type;
	int				fd;
	int				old_fd[2];
	struct	s_file	*next;
}					t_file;

typedef struct      s_cmd
{
	char            *cmd;
	struct s_file	*file;
	struct s_cmd    *next;
}                   t_cmd;

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
	t_env			*cpy;
	int				pid;
	char			**paths;
	char			**option;
	char			*exec;
	char			*binary;
	char			*pwd;
	char			*line;
	int				token;
	int				token2;
	int				ret;
	char			*value;
	t_cmd			*cmd_lst;
	t_file			*head_file;
}					t_data;

extern t_data	g_data;

char				**ft_split(const char *s, char c);
void				ft_pwd(char *line, t_data *data);
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
void				ft_echo(char *str, t_data *data);
void				ft_exit(t_data *data);
void				init_data(t_data *data);
void				try_exec(t_data *data, char *str);
int					check_line(t_data *data);
int					ft_dollar(t_data *data, int ret);
void				dollar_case(char *str, int *i, t_data *data, int check);
void				skip_white(char *str, int *i);
void				ft_ptvirgule(t_data *data);
int					ft_redir(t_data *data, char *str);
int					true_redir(char *str, int check, int *fd);
int					skip_char(char *str, int *i, char c);
void				ft_free_and_reset(char **str, int i);
void				ft_clear_file_lst(t_file **file, t_data *data);
char				*join_n_free(char *s1, char *s2, int size);

#endif
