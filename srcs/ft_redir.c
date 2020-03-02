/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:32 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/02 09:46:10 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*add_lstfile(t_file **file, t_data *data)
{
	while (*file)
		file = &(*file)->next;
	if (!((*file) = malloc(sizeof(t_file))))
		exit(-1);
	if (!data->head_file)
		data->head_file = data->cmd_lst->file;
	(*file)->filename = NULL;
	(*file)->type = -1;
	(*file)->fd = -1;
	(*file)->old_fd = dup(1);
	(*file)->next = NULL;
	return (*file);
}

char	*get_filename(char *str, int i)
{
	int		j;
	int		k;
	char	*save;

	j = i;
	save = NULL;
	skip_white(str, &j);
	k = j;
	while (str[j])
	{
		if (str[j] == '>' || str[j] == '<' || str[j] == ' ')
			return (save);
		else if (str[j] == '\'')
			while (str[++j] && str[j] != '\'')
				save = join_n_free(save, ft_strndup(&str[j], 1), 1);
		else if (str[j] == '"')
			while (str[++j] && str[j] != '"')
				save = join_n_free(save, ft_strndup(&str[j], 1), 1);
		else
			save = join_n_free(save, ft_strndup(&str[j], 1), 1);
		j++;
	}
	return (save);
}

int		ft_add_filename(t_data *data, char *str, int *i, int *j)
{
	t_file	*file;

	file = add_lstfile(&data->cmd_lst->file, data);
	if (str[*i] == '>' && str[*i + 1] && str[*i + 1] != '>')
		file->type = 1;
	else if (str[*i] == '>' && str[*i + 1] && str[*i + 1] == '>')
		file->type = 2;
	else if (str[*i] == '<')
		file->type = 3;
	if (str[*i + 1] && str[*i + 1] == '>')
		++*i;
	++*i;
	if (!(file->filename = get_filename(str, *i)))
		return (-1);
	++*j;
	return (1);;
}

int		handle_redir(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_lst->file = data->head_file;
	while (data->cmd_lst->file)
	{
		ft_printf(2, "%d:%s\n", data->cmd_lst->file->type, data->cmd_lst->file->filename);
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
			if (++i == -1 || skip_char(str, &i, str[i - 1]) == -1)
				return (-1);
		if ((str[i] == '>' && str[i + 1] == '>') || str[i] == '>' ||
				str[i] == '<')
			if (ft_add_filename(data, str, &i, &j) == -1)
				return (-1);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			if (++i == -1 || skip_char(str, &i, str[i - 1]) == -1)
				return (-1);
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
