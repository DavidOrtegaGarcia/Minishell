/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/05/08 16:37:37 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	(void)argv;
	(void)env;
	if (argc != 1)
		return(printf("Wrong number of arguments\n"), -1);
	while (1)
	{
		char *line;
    	line = readline("Ingresa una línea de texto: ");
		printf("La línea ingresada es: %s\n", line);
	}	
}
