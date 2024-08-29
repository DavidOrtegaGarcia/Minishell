/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:45:03 by daortega          #+#    #+#             */
/*   Updated: 2024/08/28 17:08:35 by daortega         ###   ########.fr       */
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
		if (WTERMSIG(child_status) == CTRL_C)
			*exec.status = 130;
		else if (WTERMSIG(child_status) == CTRL_BS)
		{
			*exec.status = 131;
			perror("Quit (core dumped)\n");
		}
	}
}

static void	exec_command(t_com *l_com, t_env **l_env, t_exec exec, int *status)
{
	char	*path;
	char	**env;

	path = NULL;
	if (l_com->next != NULL)
		dup2(exec.fd[1], STDOUT_FILENO);
	close_pipe(exec.fd[0], exec.fd[1]);
	make_redirections(l_com->redir, CHILD);
	if (l_com->command != NULL)
	{
		if (check_builtin(l_com->command) == 1)
		{
			builtins(l_com, l_env, status);
			exit(EXIT_SUCCESS);
		}
		path = find_path(l_com->command[0], *l_env);
	}
	env = convert_env(*l_env);
	execve(path, l_com->command, env);
	exit(EXIT_SUCCESS);
}

static void	make_exec(t_com *l_command, t_env **l_env, t_exec exec, int *status)
{
	signals(CHILD);
	if (pipe(exec.fd) == -1)
		return (perror(MSG_PFE), exit(EXIT_FAILURE));
	exec.pids[exec.i] = fork();
	if (exec.pids[exec.i] < 0)
		return (perror(MSG_FORK_F), exit(EXIT_FAILURE));
	else if (exec.pids[exec.i] == 0)
		exec_command(l_command, l_env, exec, status);
	dup2(exec.fd[0], STDIN_FILENO);
	close_pipe(exec.fd[0], exec.fd[1]);
}

void	execute(t_com *l_command, t_env **l_env, int *status)
{
	t_exec	exec;

	if (l_command == NULL)
		return ;
	exec = fill_exec(status, l_command);
	exec.i = 0;
	while (l_command != NULL)
	{
		if (check_builtin(l_command->command) == 1 && exec.n_com == 1
			&& l_command->command != NULL)
		{
			make_redirections(l_command->redir, DEFAULT);
			builtins(l_command, l_env, status);
		}
		else
			make_exec(l_command, l_env, exec, status);
		exec.i++;
		l_command = l_command->next;
	}
	set_std_default(exec);
	the_whatipids(exec);
}
