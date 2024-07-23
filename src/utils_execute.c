/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:04:39 by daortega          #+#    #+#             */
/*   Updated: 2024/07/23 15:59:19 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_exec	fill_exec(char *env, int *status, int n_com)
{
	t_exec	exec;

	exec.env = env;
	exec.status = status;
	exec.n_com = n_com;
	exec.pids = malloc(n_com * sizeof(pid_t));
	if (exec.pids == NULL)
		return (perror(MSG_MLC_F), exit(MLC_F), exec);
	if (pipe(exec.fd) == -1)
		return (perror(MSG_PFE), exit(PFE), exec);
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
