/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:30:15 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/01 23:02:39 by gaefourn         ###   ########.fr       */
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

int		count_pipe(t_pipe **pipe, char **str)
{
	int		i;
	int		check;
	char	*tmp;

	i = -1;
	check = 0;
	tmp = NULL;
	while ((*str)[++i])
	{
		if (norme_ft_count_pipe(*str, i, tmp) == -1)
			return (-1);
		if ((*str)[i] == '"' || (*str)[i] == '\'')
			check += 1;
		else if ((*str)[i] == '|' && check % 2 == 0)
		{
			if (ft_norme_pipe(str, &i, &tmp, pipe) == -1)
				return (-1);
		}
	}
	add_pipe(pipe, ft_substr(*str, 0, i));
	free_string(str);
	return (0);
}

void	ft_pipe(t_pipe *pipes, t_data *data, char *tmp, int check)
{
	int		fd[2];

	pipe(fd);
	if (pipes->next)
	{
		if (!(data->pid1 = fork()) && close(fd[0]) != -1)
		{
			dup2(fd[1], 1);
			la_norme(data, tmp);
		}
	}
	else
		la_norme(data, tmp);
	wait(NULL);
	if (!(data->pid2 = fork()) && close(fd[1]) != -1)
	{
		dup2(fd[0], 0);
		ft_norme_main_pipe(pipes, data, check, tmp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(data->pid2, &data->ret, 0);
	data->ret /= 256;
	if (check != 0)
		exit(data->ret);
}
