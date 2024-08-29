/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:07:17 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 14:46:38 by daortega         ###   ########.fr       */
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

t_env	*get_ev(char *line, int k, t_env *l_env)
{
	int	i;
	int	j;

	j = k;
	i = 0;
	while (ft_isalpha(line[j]) == 1)
	{
		i++;
		j++;
	}
	while (compare_key(&line[k], l_env->key) != 0)
		l_env = l_env->next;
	return (l_env);
}

int	check_ev(char *line, t_env *l_env)
{
	while (l_env != NULL)
	{
		if (compare_key(line, l_env->key) == 0 && l_env->list != 1
			&& l_env->value[0] != '\0')
			return (1);
		l_env = l_env->next;
	}
	return (0);
}
