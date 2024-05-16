/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:52:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/05/16 14:32:36 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	parse_input(int argc, char **argv, char **envp)
{
	if (argc <= 0)
	{
		printf("Running with no commands\n");
		return (-1);
	}
	if (argv[0][0] != '.' && argv[0][0] != '/' && argv[0][0] != '~')
		return (1);
	if (envp[0] == NULL)
	{
		printf("running with no environment variables\n");
		return (-1);
	}
	return (0);
}
