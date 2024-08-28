/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:46:42 by daortega          #+#    #+#             */
/*   Updated: 2024/08/28 13:55:57 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf ("%s=%s\n", l_env->key, l_env->value);
		l_env = l_env->next;
	}
}

void	get_size_value(int *i, int *j, char *env)
{
	while (env[*i] != '=')
		(*i)++;
	(*i)++;
	while (env[*i] != '\0')
	{
		(*i)++;
		(*j)++;
	}
}

static char	*find_value(char *env)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	get_size_value(&i, &j, env);
	value = malloc((j + 1) * sizeof(char));
	if (value == NULL)
		return (perror(MSG_MLC_F), exit(MLC_F), NULL);
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
		return (perror(MSG_MLC_F), exit(MLC_F), NULL);
	i = 0;
	while (env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

t_env	*new_node(char *env)
{
	t_env	*n_node;

	n_node = malloc(sizeof(t_env));
	if (n_node == NULL)
		return (perror(MSG_MLC_F), exit(MLC_F), NULL);
	if (env == NULL)
		return (NULL);
	if (ft_strchr(env, '=') != 0)
	{
		n_node->key = find_key(env);
		n_node->value = find_value(env);
		n_node->list = 3;
	}
	else
	{
		n_node->key = ft_strdup(env);
		if (n_node->key == NULL)
                	return (perror(MSG_MLC_F), exit(MLC_F), NULL);
		n_node->value = NULL;
		n_node->list = 1;
	}
	n_node->next = NULL;
	return (n_node);
}

t_env	*fill_l_env(char **env)
{
	t_env	*l_env;
	t_env	*next_node;
	int		i;

	if (env[0] == NULL)
		return (NULL);
	l_env = new_node(env[0]);
	next_node = l_env;
	i = 1;
	while (env[i] != NULL)
	{
		next_node->next = new_node(env[i]);
		next_node = next_node->next;
		i++;
	}
	return (l_env);
}
