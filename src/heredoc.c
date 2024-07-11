/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:02:56 by daortega          #+#    #+#             */
/*   Updated: 2024/07/11 18:10:25 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	make_heredoc(char *file, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_CREAT);
	if (fd == -1)
		return (perror(MSG_OPEN_F), exit(OPEN_F));
	line = readline("> ");
	while (line != NULL && ft_strncm(line, file, ft_strlen) != 0)
	{
		ft_putstr_fd(fd, line);
		free(line);
		line = readline("> ");
	}
	if (line != NULL)
		free(line);
}

void	check_heredoc(t_redir *redir)
{
	char	*path;
	int		i;
	char	*num;

	i = 0;
	while (redir != NULL)
	{
		if (redir->type == HERE_DOC)
		{
			num = ft_itoa(i);
			if (num == NULL)
				return (perror(MSG_MLC_F), exit(MLC_F));
			path = ft_strjoin("/tmp/heredoc_minishell", num);
			free(num);
			if (path == NULL)
				return (perror(MSG_MLC_F), exit(MLC_F));
			make_heredoc(redir->file, path);
			free(redir->file);
			redir->file = path;
			i++;
		}
		redir = redir->next;
	}
}

void	*herdoc(t_com *command)
{
	while (command != NULL)
	{
		check_heredoc(command->redir);
		command = command->next;
	}
}
