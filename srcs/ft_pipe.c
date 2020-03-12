/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:30:15 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/12 05:46:39 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_pipe(t_pipe **pipe, char *str)
{
	int	i;

	i = 0;
	skip_white(str, &i);
	while ((*pipe))
		pipe = &(*pipe)->next;
	if (!((*pipe) = malloc(sizeof(t_pipe))))
		exit(-1);
	(*pipe)->cmd = str;
	(*pipe)->file = NULL;
	(*pipe)->next = NULL;
	if (str[i] == '\0')
	{
		str[0] = '\0';
		return (str);
	}
	return ((*pipe)->cmd);
}

int		count_pipe(t_pipe **pipe, char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (str[++i])
	{
		if (norme_ft_count_pipe(str, i, tmp) == -1)
			return (-1);
		else if (str[i] == '|')
		{
			if (!*add_pipe(pipe, ft_substr(str, 0, i)))
			{
				ft_printf(2,
					"Minishell: syntax error near unexpected token `|'\n");
				free_string(&tmp);
				return (-1);
			}
			norme_ft_count_pipe2(&str, &i);
		}
	}
	add_pipe(pipe, ft_substr(str, 0, i));
	free_string(&str);
	return (0);
}

void	ft_pipe(t_pipe *pipes, t_data *data, char *tmp, int check)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pipe(fd);
	if (!(pid1 = fork()))
	{
		close(fd[0]);
		dup2(fd[1], 1);
		exit(display_output(data, tmp));
	}
	wait(NULL);
	if (!(pid2 = fork()))
	{
		close(fd[1]);
		dup2(fd[0], 0);
		if (pipes->next)
		{
			data->cmd_lst->pipe = data->cmd_lst->pipe->next;
			ft_pipe(pipes->next, data, tmp, check + 1);
		}
		else
			exit(display_output(data, tmp));
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	waitpid(pid2, &status, 0);
	if (check != 0)
		exit(status);
}
