/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:46:42 by daortega          #+#    #+#             */
/*   Updated: 2024/06/13 17:53:31 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(t_env *l_env)
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
		printf ("%s=%s\n", l_env->key, l_env->value);
		l_env = l_env->next;
	}
}

static char	*find_value(char *env)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i] != '=')
		i++;
	i++;
	while (env[i] != '\0')
	{
		i++;
		j++;
	}
	value = malloc((j + 1) * sizeof(char));
	if (value == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i] != '=')
		i++;
	i++;
	while (env[i] != '\0')
		value[j++] = env[i++];
	value[j] = '\0';
	return (value);
}

static char	*find_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	key = malloc((i + 1) * sizeof(char));
	if (key == NULL)
		return (NULL);
	i = 0;
	while (env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static t_env	*new_node(char *env)
{
	t_env	*n_node;

	n_node = malloc(sizeof(t_env));
	if (n_node == NULL)
		return (NULL);
	n_node->key = find_key(env);
	if (n_node->key == NULL)
		return (free(n_node), NULL);
	n_node->value = find_value(env);
	if (n_node->value == NULL)
		return (free(n_node->key), free(n_node), NULL);
	n_node->next = NULL;
	return (n_node);
}

t_env	*fill_l_env(char **env)
{
	t_env	*l_env;
	t_env	*next_node;
	int		i;

	if (!env)
		return (NULL);
	l_env = new_node(env[0]);
	if (l_env == NULL)
		return (NULL);
	next_node = l_env;
	i = 1;
	while (env[i] != NULL)
	{
		next_node->next = new_node(env[i]);
		if (next_node->next == NULL)
			return (free_env(l_env), NULL);
		next_node = next_node->next;
		i++;
	}
	return (l_env);
}
