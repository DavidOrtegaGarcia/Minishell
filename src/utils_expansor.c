/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:07:17 by daortega          #+#    #+#             */
/*   Updated: 2024/05/24 17:04:30 by daortega         ###   ########.fr       */
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
		result = (unsigned char)line[i] - (unsigned char)key[i];
		i++;
	}
	if ((line[i] != '\0' || key[i] != '\0') &&
		(ft_isalpha(line[i] == 1) || ft_isalpha(key[i] == 1)) && result == 0)
		result = (unsigned char)line[i] - (unsigned char)key[i];
	if (result > 0)
		result = 1;
	else if (result < 0)
		result = -1;
	return (result);
}
