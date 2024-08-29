/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:19:08 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 14:21:49 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	free_env(t_env *l_env)
{
	t_env	*aux;

	if (l_env != NULL)
	{
		while (l_env->next != NULL)
		{
			aux = l_env;
			l_env = l_env->next;
			free(l_env->key);
			free(l_env->value);
			free(aux);
		}
		free(l_env);
	}
}

void	print_env(t_env *l_env)
{
	while (l_env != NULL)
	{
		if (l_env->list == 2 || l_env->list == 3)
			ft_printf ("%s=%s\n", l_env->key, l_env->value);
		l_env = l_env->next;
	}
}
