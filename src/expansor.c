/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:30:43 by daortega          #+#    #+#             */
/*   Updated: 2024/05/22 17:45:51 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (ft_strncmp(&line[k], l_env->key, i) != 0)
		l_env = l_env->next;
	return (l_env);
}

char *put_value(char *newline, int *j, char *value)
{
	int i;

	i = 0;
	while (value[i] != '\0')
	{
		newline[*j] = value[i];
		(*j)++;
		i++;
	}
	return (newline);
}

static char	*translate_ev(char *line, int k, t_env *l_env)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	l_env = get_ev(line, k + 1, l_env);
	j = ft_strlen(line) - ft_strlen(l_env->key) + ft_strlen(l_env->value);
	newline = malloc(j * sizeof(char));
	if (newline == NULL)
		return (NULL);
	j = 0;
	while (line[i] != '\0')
	{
		if (i == k)
		{  
			newline = put_value(newline, &j, l_env->value);
			i += ft_strlen(l_env->key) + 1;
		}
		else
			newline[j++] = line[i++];
	}
	newline[j] = '\0';
	return (free(line), newline);
}

static int	check_ev(char *line, t_env *l_env)
{
	int		i;
	int		result;

	i = 0;
	result = -1;
	while (ft_isalpha(line[i]) == 1)
		i++;
	while (l_env != NULL)
	{
		if (ft_strncmp(line, l_env->key, i) == 0)
			return (1);
		l_env = l_env->next;
	}
	return (0);
}

char *expansor(char *line, t_env *l_env)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == '$' && ft_isalpha(line[i + 1]) == 1
		 	&& check_ev(&line[i + 1], l_env) == 1)
				line = translate_ev(line, i, l_env);
		/*else if (line[i] == '$' && ft_isalpha(line[i + 1]) == 1 
			&& check_ev(&line[i + 1], l_env) == 0)
			line = remove_ev(line);*/
		i++;
		//printf("line: %s\n",line);
	}
	return (line);
}
// echo '$PATH'"$USER"