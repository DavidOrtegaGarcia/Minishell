/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dav.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:45:03 by daortega          #+#    #+#             */
/*   Updated: 2024/07/29 18:15:31 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_std_default(t_exec exec)
{
	dup2(exec.default_fd[0], STDIN_FILENO);
	dup2(exec.default_fd[1], STDOUT_FILENO);
	close(exec.default_fd[0]);
	close(exec.default_fd[1]);
}

static void	the_whatipids(t_exec exec)
{
	int	i;
	int	child_status;

	i = 0;
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

static void	exec_command(t_com *t_command, t_env *l_env, t_exec exec)
{
	char	*path;

	signals(CHILD);
	path = NULL;
	if (t_command->next != NULL)
		dup2(exec.fd[1], STDOUT_FILENO);
	close_pipe(exec.fd[0], exec.fd[1]);
	make_redirections(t_command->redir);
	if (t_command->command != NULL)
	{
		built_ins(t_command);
		path = find_path(t_command->command[0], l_env);
	}
	execve(path, t_command->command, exec.env);
}

/*static void	exec_first_command(t_com *t_command, t_env *l_env, t_exec exec)
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
}*/

void	execute(t_com *t_command, t_env *l_env, char *env[], int *status)
{
	t_exec	exec;
	int		i;

	if (t_command == NULL)
		return ;
	exec = fill_exec(env, status, t_command);
	//exec_first_command(t_command, l_env, exec);
	i = 0;
	while (t_command != NULL)
	{
		if (pipe(exec.fd) == -1)
			return (perror(MSG_PFE), exit(EXIT_FAILURE));
		exec.pids[i] = fork();
		if (exec.pids[i] < 0)
			return (perror(MSG_FORK_F), exit(EXIT_FAILURE));
		else if (exec.pids[i] == 0)
			exec_command(t_command, l_env, exec);
		dup2(exec.fd[0], STDIN_FILENO);
		close_pipe(exec.fd[0], exec.fd[1]);
		i++;
		t_command = t_command->next;
	}
	set_std_default(exec);
	the_whatipids(exec);
}
