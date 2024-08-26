/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:01:54 by daortega          #+#    #+#             */
/*   Updated: 2024/08/12 15:35:57 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atol(char *str)
{
	long	i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}

int	check_builtin(char **com)
{
	if (com == NULL)
		return (0);
	if (ft_strcmp(com[0], "echo") == 0)
		return (1);
	if (ft_strcmp(com[0], "cd") == 0)
		return (1);
	if (ft_strcmp(com[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(com[0], "export") == 0)
		return (1);
	if (ft_strcmp(com[0], "unset") == 0)
		return (1);
	if (ft_strcmp(com[0], "env") == 0)
		return (1);
	if (ft_strcmp(com[0], "exit") == 0)
		return (1);
	return (0);
}
