/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:28:09 by rpocater          #+#    #+#             */
/*   Updated: 2024/06/27 15:35:29 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	ft_addmetachr(char *line, int start, int x)
{
	int	i;

	i = x;
	if (line[i] == '|')
		return (i);
	else
	{
		if (line[i + 1] == line[start])
			i++;
	}
	return (i);
}

int	ft_addprint(char *line, int x)
{
	int	i;

	i = x;
	while (line[i] != '\0')
	{
		if (ft_metachr(line[i]) == 1)
			break ;
		if (ft_metachr(line[i]) == 2)
			break ;
		i++;
	}
	return (i);
}

int	ft_addend(char *line, int x)
{
	int	i;

	i = x;
	printf("Finish quotes\n");
	while (line[i] != '\0')
	{
		i++;
	}
	return (i);
}
