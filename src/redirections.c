/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:26:45 by daortega          #+#    #+#             */
/*   Updated: 2024/08/28 16:50:28 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	out_a_redir(char *file, int mode)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (mode == CHILD)
	{
		if (fd == -1)
			return (printf(MSG_OPEN_F, file), exit(EXIT_FAILURE), 1);
	}
	else
	{
		if (fd == -1)
			return (printf(MSG_OPEN_F, file), 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

static int	out_t_redir(char *file, int mode)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (mode == CHILD)
	{
		if (fd == -1)
			return (printf(MSG_OPEN_F, file), exit(EXIT_FAILURE), 1);
	}
	else
	{
		if (fd == -1)
			return (printf(MSG_OPEN_F, file), 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

static int	hd_redir(char *file, int mode)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (mode == CHILD)
	{
		if (fd == -1)
			return (printf(MSG_OPEN_F, file), exit(EXIT_FAILURE), 1);
	}
	else
	{
		if (fd == -1)
			return (printf(MSG_OPEN_F, file), 1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

static int	in_redir(char *file, int mode)
{
	int	fd;

	write(2,"IN_REDIR AAAAAAA\n", 18);
	if (mode == CHILD)
	{
		write(2,"IN_REDIR BBBBBBB\n", 18);
		if (access(file, F_OK) == -1)
			return (perror("Me cago en tu puta madre\n"), exit(EXIT_FAILURE), 1);
		write(2,"IN_REDIR CCCCCCC\n", 18);
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (printf(MSG_OPEN_F, file), exit(EXIT_FAILURE), 1);
	}
	else
	{
		if (access(file, F_OK) == -1)
			return (printf(MSG_FDE, file), 1);
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (printf(MSG_OPEN_F, file), 1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

void	make_redirections(t_redir *redir, int mode)
{
	while (redir != NULL)
	{
		write(2,"Exec AAAAAAA\n", 14);
		int i = redir->type;
		ft_putnbr_fd(i, 2);
		write(2,"\n", 1);
		if (redir->type == IN)
			in_redir(redir->file, mode);
		else if (redir->type == HERE_DOC)
			hd_redir(redir->file, mode);
		else if (redir->type == OUT_TRUNC)
			out_t_redir(redir->file, mode);
		else if (redir->type == OUT_APPEND)
			out_a_redir(redir->file, mode);
		write(2,"Exec YYYYYYY\n", 14);
		redir = redir->next;
		write(2,"Exec ZZZZZZZ\n", 14);
	}
	write(2,"Exec FFFFFFF\n", 14);
}
