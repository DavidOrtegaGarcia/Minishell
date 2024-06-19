/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/06/19 14:23:00 by daortega         ###   ########.fr       */
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
	printf("sadsafdsa3\n");
	while (line != NULL)
	{
    	line = readline("minishell$ ");
		printf("sadsafdsa2\n");
      	if(line != NULL && line[0] != '\0') 
			add_history(line);
		printf("sadsafdsa\n");
		//parseo
  		command = ft_tokenize(line);
		printf("In main: \n");
		print_list(command);
		/*line = expansor(line, l_env, 1735);
		if (line == NULL)
			exit(EXIT_FAILURE);
		ft_printf("%s\n", line);*/
		//execute();
		free(line);
		
	}
	printf("HOLA");
}
