/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/05/13 17:52:09 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*t_env;

	(void)argv;
	(void)env;
	if (argc != 1)
		return(printf("Wrong number of arguments\n"), -1);
	t_env = fill_t_env(env);
	while (1)
	{
    	line = readline("minishell$ ");
		if (line != NULL && line[0] != '\0') 
			add_history(line);
		ft_printf("%s\n", line);
		//parseo
		expansor(line, env);
		free(line);
		
	}
}
