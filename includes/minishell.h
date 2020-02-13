/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 04:15:01 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/13 09:30:45 by glaurent         ###   ########.fr       */
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

struct dirent *readdir(DIR *dir);

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

#endif
