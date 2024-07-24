/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:07:17 by daortega          #+#    #+#             */
/*   Updated: 2024/07/24 15:05:40 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_key(char *line, char *key)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (line[i] != '\0' && key[i] != '\0' && result == 0)
	{
		result = line[i] - key[i];
		i++;
	}
	if ((line[i] != '\0' || key[i] != '\0')
		&& (ft_isalpha(line[i]) == 1 || ft_isalpha(key[i]) == 1) && result == 0)
		result = line[i] - key[i];
	if (result > 0)
		result = 1;
	else if (result < 0)
		result = -1;
	return (result);
}
