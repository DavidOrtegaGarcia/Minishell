/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/07/02 12:36:58 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;
	t_token	*list;

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
		list = ft_tokenize(line);
		printf("In main: \n");
		if (list == NULL)
			exit(EXIT_FAILURE);
		print_list(list);
		//parseo
		//line = expansor(line, l_env, 1735);
		//if (line == NULL)
			//exit(EXIT_FAILURE);
		//ft_printf("%s\n", line);
		argv = ft_lst_to_matrix(list);
		argc = count_lines(argv);
		pre_execute(argc, argv, env);
		printf("After execute\n");
		free(line);
		ft_free(argv);
		line = readline("minishell$ ");
	}
	printf("HOLA\n");
	exit(EXIT_SUCCESS);
}
