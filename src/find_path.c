/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:26:11 by daortega          #+#    #+#             */
/*   Updated: 2024/07/25 15:09:12 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_routes(t_env *l_env)
{
	char	**routes;

	while (compare_key(l_env->key, "PATH") != 0)
		l_env = l_env->next;
	routes = ft_split(l_env->value, ':');
	if (routes == NULL)
		return (perror(MSG_MLC_F), exit(MLC_F), NULL);
	return (routes);
}

char	*find_relative_path(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) == 0)
	{
		if (stat(path, &path_stat) != 0)
			return (perror("Stat failed\n"), exit(EXIT_FAILURE), NULL);
		if (S_ISDIR(path_stat.st_mode))
			return (ft_printf(MSG_IAD, path), exit(IS_A_DIR), NULL);
		if (access (path, X_OK) == 0)
			return (path);
		else
			return (ft_printf(MSG_CNA, path), exit(CMD_NO_ACCESS), NULL);
	}
	else
		return (ft_printf(MSG_NSF, path), exit(NO_SUCH_FILE), NULL);
}

char	*find_path(char *command, t_env *l_env)
{
	char	**routes;
	char	*path;
	int		i;

	i = 0;
	if (ft_strchr(command, '/') != 0)
		return (find_relative_path(command));
	routes = get_routes(l_env);
	while (routes[i] != NULL)
	{
		path = ft_strjoin_s(routes[i], command);
		if (path == NULL)
			return (perror(MSG_MLC_F), exit(MLC_F), NULL);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				return (free_matrix(routes), path);
			else
				return (ft_printf(MSG_CNA, command), exit(CMD_NO_ACCESS), NULL);
		}
		free(path);
		i++;
	}
	free_matrix(routes);
	return (ft_printf(MSG_CNF, command), exit(CMD_NOT_FOUND), NULL);
}
