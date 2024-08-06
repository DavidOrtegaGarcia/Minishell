/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:04:39 by daortega          #+#    #+#             */
/*   Updated: 2024/08/06 14:28:16 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*strjoin_env(char const *s1, char const *s2)
{
	char	*sfinal;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	sfinal = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (sfinal == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		sfinal[i] = s1[i];
		i++;
	}
	sfinal[i] = '=';
	i++;
	while (i < ft_strlen(s1) + ft_strlen(s2) + 1)
		sfinal[i++] = s2[j++];
	sfinal[i] = '\0';
	return (sfinal);
}

static int	get_size_env(t_env *l_env)
{
	int	i;

	i = 0;
	while (l_env != NULL)
	{
		i++;
		l_env = l_env->next;
	}
	return (i);
}

char	**convert_env(t_env *l_env)
{
	int		s_env;
	char	**env;
	int		i;

	i = 0;
	s_env = get_size_env(l_env);
	env = malloc((s_env + 1) * sizeof(char *));
	if (env == NULL)
		return (perror(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
	while (l_env != NULL)
	{
		env[i] = strjoin_env(l_env->key, l_env->value);
		if (env == NULL)
			return (perror(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
		i++;
		l_env = l_env->next;
	}
	env[i] = NULL;
	return (env);
}

void	close_pipe(int in, int out)
{
	close(in);
	close(out);
}

t_exec	fill_exec(int *status, t_com *t_command)
{
	t_exec	exec;

	exec.status = status;
	exec.n_com = get_n_commands(t_command);
	exec.pids = malloc(exec.n_com * sizeof(pid_t));
	if (exec.pids == NULL)
		return (perror(MSG_MLC_F), exit(EXIT_FAILURE), exec);
	exec.default_fd[0] = dup(STDIN_FILENO);
	if (exec.default_fd[0] == -1)
		return (perror(MSG_DF), exit(EXIT_FAILURE), exec);
	exec.default_fd[1] = dup(STDOUT_FILENO);
	if (exec.default_fd[1] == -1)
		return (perror(MSG_DF), exit(EXIT_FAILURE), exec);
	return (exec);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	*ft_strjoin_s(char const *s1, char const *s2)
{
	char	*sfinal;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	sfinal = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (sfinal == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		sfinal[i] = s1[i];
		i++;
	}
	sfinal[i] = '/';
	i++;
	while (i < ft_strlen(s1) + ft_strlen(s2) + 1)
		sfinal[i++] = s2[j++];
	sfinal[i] = '\0';
	return (sfinal);
}

int	get_n_commands(t_com *command)
{
	int	i;

	i = 0;
	while (command != NULL)
	{
		i++;
		command = command->next;
	}
	return (i);
}
