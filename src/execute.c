/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:59:11 by rpocater          #+#    #+#             */
/*   Updated: 2024/05/13 14:47:22 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_free(char **str)
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
	while (path[i] != NULL)
	{
		route = ft_strjoin(path[i], com);//heap overflow
		execve(route, argv, envp);
		i++;
	}
	printf("Could not find any path for %s\n", com);
	ft_free(path);
	free(route);
	free(com);
	return (-1);
}

void	pre_execute(int argc, char **argv, char **envp)
{
	if (argc < 2)
	{
		printf("Wrong number of arguments\n");
		return ;
	}
	argv++; //skip the name of the executable
	//check for valid inputs
	if (argv[0][0] != '.' && argv[0][0] != '/' && argv[0][0] != '~')
	{
		if (path_execute(argv[0], argv, envp) == -1)//heap overflow
			perror("Could not path_execute");
	}
	return ;
}