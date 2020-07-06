/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:06:18 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/06 22:22:10 by gaefourn         ###   ########.fr       */
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

typedef struct		s_s
{
	char	**strs;
	int		len;
	int		i;
	int		j;
	int		k;
}					t_s;

typedef struct		s_file
{
	char			*filename;
	int				type;
	int				fd;
	int				old_fd[2];
	struct s_file	*next;
}					t_file;

typedef struct		s_pipe
{
	char			*cmd;
	struct s_file	*file;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_cmd
{
	t_pipe			*pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_data
{
	pid_t			pid1;
	pid_t			pid2;
	int				status;
	char			*uvar;
	char			*tmp;
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
	char			**quote;
	char			*ultimate_check;
	char			**ultimate_tab;
	t_cmd			*cmd_lst;
	t_file			*head_file;
	int				retpipe;
	int				ufree;
	int				checkcd;
	int				check_ret;
}					t_data;

extern t_data	g_data;

char				**ft_split(const char *s, char c);
char				**ft_splitv2(const char *s, char c, t_data *data);
void				ft_pwd(char *line, t_data *data);
int					is_builtin(char *str, t_data *data);
void				init_env(t_env **env, char **envp);
int					where_am_i(t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, int n);
int					check_char(char *str, char c);
int					get_paths(t_data *data);
char				*find_key_value(t_env *env, char *key);
char				**ft_split_env(t_env *env);
void				ft_export(char *str, t_env **env, t_data *data);
void				add_new_elem(t_env **env, char *key, char *value);
void				ft_unset(char *str, t_data *data);
void				ft_echo(char *str, t_data *data);
void				ft_exit(t_data *data, char *str);
void				init_data(t_data *data);
void				try_exec(t_data *data, char *str);
int					check_line(t_data *data);
int					ft_dollar(t_data *data, int ret);
void				dollar_case(char *str, int *i, t_data *data, int check);
void				skip_white(char *str, int *i);
int					ft_ptvirgule(t_data *data);
int					ft_redir(t_data *data, char *str);
int					true_redir(char *str, int check, int *fd, t_data *data);
int					skip_char(char *str, int *i, char c);
void				ft_free_and_reset(char **str, int i);
void				ft_clear_file_lst(t_file **file, t_data *data);
char				*join_n_free(char *s1, char *s2, int size);
int					ft_norme_builtins1(char *str, t_data *data, int i);
int					ft_norme_builtins2(char *str, t_data *data, int i);
int					ft_norme_builtins3(char *str, t_data *data, int i);
int					ft_norme_builtins4(char *str, t_data *data, int i);
void				ft_env(t_data *data);
void				ft_cd(char *str, char **here, t_data *data);
void				display_sort(t_data *data);
char				*get_next_word(char *str, int *i);
void				norme_ft_echo(char *str, int *i, t_data *data);
int					simple_quote(char *str, int *i);
int					double_quote(char *str, int *i, t_data *data);
int					norme_ft_export(t_env **env, char *key, char *value);
void				norme_ft_unset(t_data *data, t_env *copy, t_env *prev,
		char *key);
int					norme_ft_redir(t_data *data, char *str, int *i, int *j);
int					ft_add_filename(t_data *data, char *str, int *i, int *j);
void				free_lst(t_file *file);
void				free_tab(char ***tab);
void				free_string(char **str);
void				get_exec(char *str, t_data *data);
char				*get_option(char *str);
char				*is_exec(char *str, t_data *data);
void				set_up_all(t_data *data, t_cmd **head, char **envp);
void				handle_sigquit(int signum);
void				handle_sigint(int signum);
void				main_loop(t_data *data, t_cmd *head);
void				check_ls(char *str, t_data *data);
void				free_lst_cmd(t_cmd **cmd);
int					count_pipe(t_pipe **pipe, char **str);
void				free_pipe(t_pipe **pipe);
void				norme_ft_ptvirgule2(char **str, int *i);
void				ft_pipe(t_pipe *pipes, t_data *data, char *tmp, int check);
int					norme_ft_main_loop(t_data *data);
int					display_output(t_data *data, char *tmp);
void				norme_ft_count_pipe2(char **str, int *i);
int					norme_ft_count_pipe(char *str, int i, char *tmp);
void				ft_atoi_exit(char *str, int i);
int					ft_norme_pipe(char **str, int *i, char **tmp,
		t_pipe **pipe);
char				*add_pipe(t_pipe **pipe, char *str);
void				ft_norme_main_pipe(t_pipe *pipes, t_data *data, int check,
		char *tmp);
void				norme_ft_cd(char *str, t_data *data);
void				ft_strdupv2(char *str, t_data *data);
char				*quote_ereaser(char *str);
int					ultimate_check(t_data *data);
char				*ft_ultimate_norme(char *tmp, t_data *data);
void				norme_ft_export_bis(t_data *data, char **key,
		char **value, int egal);
void				la_norme(t_data *data, char *tmp);
void				norme_relink(char **str, int i, t_data *data);
void				norme_quote_ereaser(char *str, char **cpy, int *i, int *j);
int					return_value(t_data *data);
void				norme_display_output(t_data *data);
void				free_main_loop(t_data *data);
void				norme_splitv2(t_s *t, char c, const char *s);
int					norme_splitv2v2(t_s *t, char c, const char *s);
void				init_t(t_s *t);
char				*put_string_around(char *str, char *c, int pos, int keep);
int					redir_error(t_data *data);
int					check_string(char *str);
void				lol(char **key, char **value);
int					norme_env(t_data *data);

#endif
