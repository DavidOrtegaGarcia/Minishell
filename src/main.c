/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/05/08 14:46:40 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_free(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}
char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (*envp != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (printf("Did not find PATH\n"), "\0");
}
int	path_execute(char *com, char **argv, char **envp)
{
	char	*route;
	char	**path;
	int		i;

	i = 0;
	com = ft_strjoin("/", com);
	path = ft_split(find_path(envp), ':');
	while (path != NULL)
	{
		route = ft_strjoin(path[i], com);
		execve(route, argv, envp);
		i++;
	}
	ft_free(path);
	free(route);
	free(com);
	return (-1);
}
int	main(int argc, char *argv[], char *envp[])
{
	if (argc < 2)
		return(printf("Wrong number of arguments\n"), -1);
	argv++; //skip the name of the executable
	//check for valid inputs
	if (path_execute(argv[0], argv, envp) == -1)
		perror("Could not path_execute");
}
