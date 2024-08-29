/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:31:24 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 14:33:18 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	zerocase(char *num, int neg)
{
	int	i;

	i = 0;
	if (neg == 1)
		i++;
	while (num[i] != '\0')
	{
		if (num[i] != '0')
		{
			if (neg == 1 && i != 1)
			{
				num[i - 1] = '-';
				return (i - 1);
			}
			if (neg == 1 && i == 1)
				return (0);
			return (i);
		}
		i++;
	}
	return (0);
}
