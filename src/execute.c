/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:59:11 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/24 15:50:21 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

/*void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}

char	*find_path(char **envp, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (*envp != NULL)
	{
		if (ft_strncmp(str, envp[i], len) == 0)
			return (envp[i] + len);
		i++;
	}
	return (printf("Did not find %s\n", str), "\0");
}

int	path_execute(char *com, char **argv, char **envp)
{
	char	*route;
	char	**path;
	int		i;

	i = 0;
	com = ft_strjoin("/", com);
	path = ft_split(find_path(envp, "PATH="), ':');
	while (path[i] != NULL)
	{
		route = ft_strjoin(path[i], com);
		execve(route, argv, envp);
		i++;
	}
	printf("Could not find any path for %s\n", com);
	ft_free(path);
	free(route);
	free(com);
	return (-1);
}

int	direction_execute(char *com, char **argv, char **envp)
{
	//int	i;

	//i = 0;
	if (com[0] == '~')
		com = ft_strjoin(find_path(envp, "HOME="), com + 1);
	if (com[0] == '.')
	{
		//while (com[i] == '.')
		//{
		//	i++;
		//}
		com = ft_strjoin(find_path(envp, "PWD="), com + 1);
	}
	execve(com, argv, envp);
	return (-1);
}

void	pre_execute(int argc, char **argv, char **envp)
{
	if (parse_input(argc, argv, envp) == -1)
	{
		printf("The arguments did not pass the parse process\n");
		return ;
	}
	else if (parse_input(argc, argv, envp) == 2)
	{
		if (path_execute(argv[0], argv, envp) == -1)
			perror("Could not path_execute");
	}
	else if (parse_input(argc, argv, envp) == 1)
	{
		if (direction_execute(argv[0], argv, envp) == -1)
			printf("Could not non path execve\n");
	}
	return ;
}*/
