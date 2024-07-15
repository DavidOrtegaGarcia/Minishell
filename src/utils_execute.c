/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:04:39 by daortega          #+#    #+#             */
/*   Updated: 2024/07/15 16:56:46 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


t_exec fill_exec(char *env, int *status, int n_com)
{
	t_exec exec;

	exec.env = env;
	exec.status = status;
	exec.pids = malloc(n_com * sizeof(int));
	if (pipe(exec.fd) == -1) 
		return (perror(MSG_PFE), exit(PFE), NULL);
	if (exec.pids == NULL)
		return (perror(MSG_MLC_F), exit(MLC_F), NULL);
	return(exec);
}
void free_matrix(char **matrix)
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

char	*find_path(char *command, t_env *l_env)
{
	char	**routes;
	char	*path;
	int		i;

	i = 0;
	while(compare_key(l_env->key, "PATH") != 0)
		l_env = l_env->next;
	routes = ft_split(l_env->value, ':');
	if (routes == NULL)
		return(perror(MSG_MLC_F), exit(MLC_F), NULL);
	while (routes[i] != NULL)
	{
		path = ft_strjoin_s(routes[i], command);
		if (path == NULL)
			return (perror(MSG_MLC_F), exit(MLC_F), NULL);
		if (access(path, F_OK) == 0)
			return (free_matrix(routes), path);
		free(path);
		i++;
	}
	return(free_matrix(routes), NULL);

}

int get_commands(t_com *command)
{
	int	i = 0;
	while (command != NULL)
	{
		i++;
		command = command->next;
	}  
	return (i);
}
