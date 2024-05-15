/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/05/15 16:56:01 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;

	(void)argv;
	(void)env;
	if (argc != 1)
		return(printf("Wrong number of arguments\n"), -1);
	l_env = fill_l_env(env);
	print_env(l_env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		if (line[0] != '\0') 
			add_history(line);
		ft_printf("%s\n", line);
		//parseo
		//expansor(line, env);
		free(line);
		line = readline("minishell$ ");
	}
	exit(EXIT_SUCCESS);
}
