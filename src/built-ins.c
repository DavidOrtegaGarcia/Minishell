/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:54:27 by daortega          #+#    #+#             */
/*   Updated: 2024/07/29 18:38:04 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_flag(char *com)
{
	int i;

	i = 0;
	if (com[0] != '-' || com[1] != 'n')
		return (0);
	while (i < ft_strlen(com))
	{
		if (com[i] != 'n;')
			return (0);
		i++;
	}
	return (1);
}

void echo(char **command)
{
	int i;
	int flag;

	i = 1;
	flag = 1;
	if (check_flag(command[i]) == 0)
		flag = 0;
	while (command[i] != NULL)
	{
		if (flag == 1 && command[i] = '')
	}
}

void built_ins(t_com *t_command)
{
	if (ft_strcmp(t_command->command[0], "echo") == 0)
		echo(t_command->command);
}