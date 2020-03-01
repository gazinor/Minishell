/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:32 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/02 00:58:02 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_redir(t_data *data, char *str)
{
	int i;
	int	j;

	i = -1;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_char(str, &i, str[i]);
		if ((str[i + 1] && str[i] == '>' && str[i + 1] == '>') ||
			str[i] == '>' || str[i] == '<')
		{
			if (j++ == 0)
			{
				free(data->cmd_lst->cmd);
				data->cmd_lst->cmd = ft_substr(str, 0, i);
			}
			
		}
		i++;
	}
}
