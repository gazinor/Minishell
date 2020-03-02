/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:49:49 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/02 20:10:44 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		true_redir(char *str, int check, int *fd)
{
	errno = 0;
	ft_printf(2, "%s check : %d fd : %d\n",str, check, *fd);
	if (check == 1)
		*fd = open(str, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	else if (check == 2)
		*fd = open(str, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	else if (check == 3)
	{
		if ((*fd = open(str, O_RDONLY)) == -1)
		{
			ft_printf(2, "Minishell: %s: %s\n", str, strerror(errno));
			return (-1);
		}
		dup2(*fd, 0);
		return (0);
	}
	if (*fd < 0)
	{
		ft_printf(2, "Minishell: %s: %s\n", str, strerror(errno));
		return (-1);
	}
	dup2(*fd, 1);
	return (0);
}

void	ft_free_and_reset(char **str, int i)
{
	char	*tmp;

	tmp = ft_substr(*str, 0, i);
	free(*str);
	*str = tmp;
}

void	ft_clear_file_lst(t_file **file, t_data *data)
{
	while (*file)
	{
		free((*file)->filename);
		(*file)->filename = NULL;
		close((*file)->fd);
		dup2((*file)->old_fd[0], 0);
		dup2((*file)->old_fd[1], 1);
		file = &(*file)->next;
	}
	free(data->head_file);
	data->head_file = NULL;;
}
