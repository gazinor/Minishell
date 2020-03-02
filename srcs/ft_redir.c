/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:32 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/02 04:32:51 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lstfile(t_file **file)
{
	while (*file)
		file = &(*file)->next;
	if (!((*file) = malloc(sizeof(t_file))))
		exit(-1);
	(*file)->filename = NULL;
	(*file)->type = -1;
	(*file)->fd = -1;
	(*file)->next = NULL;
}

char	*get_filename(char *str, int i)
{
	int j;
	int	k;

	j = i;
	skip_white(str, &j);
	k = j;
	while (str[j])
	{
		if (str[j] == '>' || str[j] == '<')
			return (ft_substr(str, k, j));
		j++;
	}
	return (ft_substr(str, k, j));
}

void	ft_add_filename(t_data *data, char *str, int *i, int *j)
{
	add_lstfile(&data->cmd_lst->file);
	if (*j == 0)
		data->head_file = data->cmd_lst->file;
	if (str[*i] == '>' && str[*i + 1] && str[*i + 1] != '>')
		data->cmd_lst->file->type = 1;
	else if (str[*i] == '>' && str[*i + 1] && str[*i + 1] == '>')
		data->cmd_lst->file->type = 2;
	else if (str[*i] == '<')
		data->cmd_lst->file->type = 3;
	++*i;
	if (str[*i + 1] && str[*i + 1] == '>')
		++*i;
	data->cmd_lst->file->filename = get_filename(str, *i);
	++*j;
}

int		handle_redir(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_lst->file)
	{
		if (true_redir(data->cmd_lst->file->filename, data->cmd_lst->file->type,
				&i, &data->cmd_lst->file->fd) == -1)
			return (-1);
		++i;
		data->cmd_lst->file = data->cmd_lst->file->next;
	}
	return (0);
}

int	ft_redir(t_data *data, char *str)
{
	int i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_char(str, &i, str[i]);
		if ((str[i] == '>' && str[i + 1] == '>') || str[i] == '>' ||
				str[i] == '<')
			ft_add_filename(data, str, &i, &j);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_char(str, &i, str[i]);
		if (str[i] == '>' || str[i] == '<')
		{
			ft_free_and_reset(&data->cmd_lst->cmd, i);
			break ;
		}
	}
	if (handle_redir(data) == -1)
		return (-1);
	return (0);
}
