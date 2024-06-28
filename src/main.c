/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/06/22 14:12:46 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;
	t_token	*command;

	(void)argv;
	if (argc != 1)
		return (printf("Wrong number of arguments\n"), -1);
	signals();
	l_env = fill_l_env(env);
	if (l_env == NULL)
		return (printf("Error allocating memory\n"), exit(EXIT_FAILURE), -1);
	//print_env(l_env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		if (line != NULL && line[0] != '\0')
			add_history(line);
		//parseo
		command = ft_tokenize(line);
		printf("In main: \n");
		if (command == NULL)
			exit(EXIT_FAILURE);
		print_list(command);
		//ft_free_list(command);
		//line = expansor(line, l_env, 1735);
		//if (line == NULL)
			//exit(EXIT_FAILURE);
		//ft_printf("%s\n", line);
		//execute();
		free(line);
		ft_free_list(command);
		line = readline("minishell$ ");
	}
	printf("HOLA\n");
	exit(EXIT_SUCCESS);
}
