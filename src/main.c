/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/06/06 15:39:07 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_lines(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;

	if (argc != 1)
		return (printf("Wrong number of arguments\n"), -1);
	l_env = fill_l_env(env);
	//print_env(l_env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		if (line[0] != '\0') 
			add_history(line);
		//ft_printf("%s\n", line);
		//parseo
		line = expansor(line, l_env, 1735);
		if (line == NULL)
			exit(EXIT_FAILURE);
		ft_printf("%s\n", line);
		free(line);
		line = readline("minishell$ ");
	}
	exit(EXIT_SUCCESS);
}
