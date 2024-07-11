/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dav.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:45:03 by daortega          #+#    #+#             */
/*   Updated: 2024/07/11 17:24:14 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int out_a_redir(char *file, int *status)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), *status = FDE, -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int out_t_redir(char *file, int *status)
{
	int fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), *status = FDE, -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int hd_redir(char *file, int *status)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), *status = FDE, -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int in_redir(char* file, int *status)
{
	int fd;

	if (access(file, F_OK ) == -1)
		return(printf(MSG_FDE, file), *status = FDE, -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), *status = FDE, -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return(0);
}

int make_redirections(t_redir *redir, int *status)
{
	int fd[2];
	
	while (redir != NULL)
	{
		if (redir->type = IN)
			return(in_redir(redir->file, status));
		else if (redir->type = HERE_DOC)
			return (in_redir(redir->file, status));
		else if (redir->type = OUT_TRUNC)
			return (out_t_redir(redir->file, status));
		else if (redir->type = OUT_APPEND);
			return (out_a_redir(redir->file, status));
		redir = redir->next;
	}
	return (0);
}

int exec_command(t_com *command, t_env l_env, char *env[], int *status)
{
	int path;
	int pid;

	pid = fork();
	if (pid < 0)
		return (perror(MSG_FORK_F), exit(EXIT_FAILURE), -1);
	if (pid == 0)
	{
		if (make_redirections(command->redir, status) != 0);
			return (-1);
		path = find_path(command->command[0], l_env);
		if (path == NULL)
			return(perror(MSG_CNR), *status = CNR);
		execve(path, command, env);
	}
	return (0);
}

int    execute(t_com *command, t_env l_env, char *env[], int *status)
{
	int *pids;
	int n_com;

	n_com = get_commands(command);
	if (n_com == 1)
		return (exec_command(command, l_env, env ,status));
	pids = malloc(n_com * sizeof(int));
	if (pids == NULL)
		return (perror(MSG_MLC_F), exit(EXIT_FAILURE), -1);
	return (0);
}
