/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dav.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:45:03 by daortega          #+#    #+#             */
/*   Updated: 2024/07/15 17:05:51 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void out_a_redir(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), exit(OPEN_F));
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void out_t_redir(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), exit(OPEN_F));
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void hd_redir(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), exit(OPEN_F));
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void in_redir(char* file)
{
	int fd;

	if (access(file, F_OK ) == -1)
		return(printf(MSG_FDE, file), exit(FDE));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf(MSG_OPEN_F, file), exit(OPEN_F));
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int make_redirections(t_redir *redir)
{
	int fd[2];
	
	while (redir != NULL)
	{
		if (redir->type = IN)
			in_redir(redir->file);
		else if (redir->type = HERE_DOC)
			in_redir(redir->file);
		else if (redir->type = OUT_TRUNC)
			out_t_redir(redir->file);
		else if (redir->type = OUT_APPEND);
			out_a_redir(redir->file);
		redir = redir->next;
	}
	return (0);
}

void exec_one_command(t_com *command, t_env *l_env, char *env[], int *status)
{
	int path;
	int pid;
	int child_status;

	pid = fork();
	if (pid < 0)
		return (perror(MSG_FORK_F), exit(EXIT_FAILURE), -1);
	if (pid == 0)
	{
		make_redirections(command->redir);
		path = find_path(command->command[0], l_env);
		if (path == NULL)
			return(perror(MSG_CNR), exit(MSG_CNR));
		execve(path, command, env);
	}
	waitpid(pid, &child_status, 0);
	if (WIFEXITED(child_status))
		*status = WEXITSTATUS(status);
}

void    execute(t_com *command, t_env *l_env, char *env[], int *status)
{
	t_exec exec;
	int n_com;
	int i;

	n_com = get_commands(command);
	if (n_com == 1)
		return (exec_one_command(command, l_env, env, status));
	exec = fill_exec(env, status, n_com);
	i = 0;
	exec_first_command(command, l_env, exec);
	while(i < n_com)
	{
		exec.pids[i] = fork();
		if (exec.pids[i] < 0)
			return (perror(MSG_FORK_F), exit(EXIT_FAILURE), -1);
		if (exec.pids[i] == 0)
			exec_command();
		i++;
		command = command->next;
	}
	return (0);
}
