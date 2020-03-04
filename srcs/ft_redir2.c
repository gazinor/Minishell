/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:49:49 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/04 03:43:07 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		true_redir(char *str, int check, int *fd)
{
	errno = 0;
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
	data->head_file = NULL;
}

int		norme_ft_redir(t_data *data, char *str, int *i, int *j)
{
	while (str[++*i])
	{
		if (str[*i] == '\'' || str[*i] == '"')
			if (++*i == -1 || skip_char(str, i, str[*i - 1]) == -1)
				return (-1);
		if ((str[*i] == '>' && str[*i + 1] == '>') || str[*i] == '>' ||
				str[*i] == '<')
			if (ft_add_filename(data, str, i, j) == -1)
				return (-1);
	}
	return (0);
}
