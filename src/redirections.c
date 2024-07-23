/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:26:45 by daortega          #+#    #+#             */
/*   Updated: 2024/07/23 16:10:03 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	out_a_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), exit(OPEN_F));
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	out_t_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), exit(OPEN_F));
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	hd_redir(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), exit(OPEN_F));
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	in_redir(char *file)
{
	int	fd;

	if (access(file, F_OK) == -1)
		return (printf(MSG_FDE, file), exit(FDE));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), exit(OPEN_F));
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	make_redirections(t_redir *redir)
{
	while (redir != NULL)
	{
		if (redir->type == IN)
			in_redir(redir->file);
		else if (redir->type == HERE_DOC)
			in_redir(redir->file);
		else if (redir->type == OUT_TRUNC)
			out_t_redir(redir->file);
		else if (redir->type == OUT_APPEND)
			out_a_redir(redir->file);
		redir = redir->next;
	}
}
