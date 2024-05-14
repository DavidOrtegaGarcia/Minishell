/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/05/14 13:54:13 by rpocater         ###   ########.fr       */
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
	char *line;
	(void)argv;
	(void)env;
	char **command;
	if (argc != 1)
		return(printf("Wrong number of arguments\n"), -1);
	while (1)
	{
    	line = readline("minishell$ ");
		if(line != NULL && line[0] != '\0') 
			add_history(line);
		//parseo
		//command = ft_split(line, ' ');
		command = ft_tokenize(line);
		argc = count_lines(command);
		pre_execute(argc, command, env);
		free(line);
		
	}
	printf("HOLA");
}
