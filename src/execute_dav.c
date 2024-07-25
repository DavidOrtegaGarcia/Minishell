/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dav.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:45:03 by daortega          #+#    #+#             */
/*   Updated: 2024/07/25 15:19:02 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	the_whatipids(t_exec exec)
{
	int	i;
	int	child_status;

	i = 0;
	close(exec.fd[0]);
	close(exec.fd[1]);
	while (i < exec.n_com)
	{
		waitpid(exec.pids[i], &child_status, 0);
		i++;
	}
	free(exec.pids);
	if (WIFEXITED(child_status))
		*exec.status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
	{
		if (WTERMSIG(child_status) == SIGINT)
			*exec.status = 130;
		else if (WTERMSIG(child_status) == SIGQUIT)
		{
			*exec.status = 131;
			perror("Quit (core dumped)\n");
		}
	}
}

static void	exec_command(t_com *t_command, t_env *l_env, t_exec exec, int i)
{
	char	*path;

	signals(CHILD);
	path = find_path(t_command->command[0], l_env);
	dup2(exec.fd[0], STDIN_FILENO);
	close(exec.fd[0]);
	if (i != exec.n_com -1)
		dup2(exec.fd[1], STDOUT_FILENO);
	close(exec.fd[1]);
	make_redirections(t_command->redir);
	execve(path, t_command->command, exec.env);
}

static void	exec_first_command(t_com *t_command, t_env *l_env, t_exec exec)
{
	char	*path;
	exec.pids[0] = fork();
	if (exec.pids[0] < 0)
		return (perror(MSG_FORK_F), exit(FORK_F));
	if (exec.pids[0] == 0)
	{
		signals(CHILD);
		path = NULL;
		if (t_command->command != NULL)
			path = find_path(t_command->command[0], l_env);
		close(exec.fd[0]);
		if (exec.n_com > 1)
			dup2(exec.fd[1], STDOUT_FILENO);
		close(exec.fd[1]);
		make_redirections(t_command->redir);
		execve(path, t_command->command, exec.env);
	}
}

/*void exec_one_command(t_com *t_command, t_env *l_env, char *env[], int *status)
{
	char *path;
	int pid;
	int child_status;

	pid = fork();
	if (pid < 0)
		return (perror(MSG_FORK_F), exit(FORK_F));
	if (pid == 0)
	{
		make_redirections(t_command->redir);
		path = find_path(t_command->command[0], l_env);
		if (path == NULL)
			return(perror(MSG_CNR), exit(MSG_CNR));
		execve(path, t_command->command, env);
	}
	waitpid(pid, &child_status, 0);
	if (WIFEXITED(child_status))
		*status = WEXITSTATUS(child_status);
}*/

void	execute(t_com *t_command, t_env *l_env, char *env[], int *status)
{
	t_exec	exec;
	int		n_com;
	int		i;

	if (t_command == NULL)
		return ;
	n_com = get_n_commands(t_command);
	exec = fill_exec(env, status, n_com);
	exec_first_command(t_command, l_env, exec);
	t_command = t_command->next;
	i = 1;
	while (i < n_com)
	{
		exec.pids[i] = fork();
		if (exec.pids[i] < 0)
			return (perror(MSG_FORK_F), exit(FORK_F));
		if (exec.pids[i] == 0)
			exec_command(t_command, l_env, exec, i);
		i++;
		t_command = t_command->next;
	}
	dup2(exec.default_fd[0], STDIN_FILENO);
	dup2(exec.default_fd[1], STDOUT_FILENO);
	close(exec.default_fd[0]);
	close(exec.default_fd[1]);
	the_whatipids(exec);
}
