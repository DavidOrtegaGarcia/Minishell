/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:01:54 by daortega          #+#    #+#             */
/*   Updated: 2024/07/30 15:23:34 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_builtin(char **com)
{
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
