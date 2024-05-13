/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:46:42 by daortega          #+#    #+#             */
/*   Updated: 2024/05/13 18:10:00 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *fill_t_env(char **env)
{
	int 	i;
	t_env	*t_env;
	t_env	*aux;

	i = 1;
	t_env->key = fill_key(env[0]);
	t_env->value = fill_value(env[0]);
	t_env->prev = NULL;
	t_env->next = malloc(sizeof(t_env));
	aux = t_env;
	t_env = t_env->next;
	while (env[i] != NULL)
	{
		t_env->key = fill_key(env[i]);
		t_env->value = fill_value(env[i]);
		t_env->prev = aux; 
		t_env->next = malloc(sizeof(t_env));
		aux = t_env;
		t_env = t_env->next;
		i++;
	}
}
