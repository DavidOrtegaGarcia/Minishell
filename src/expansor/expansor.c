/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:30:43 by daortega          #+#    #+#             */
/*   Updated: 2024/05/21 17:05:05 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_ev(char *line, int k, t_env *l_env)
{
	int	exit;
	int	i;
	int	j;

	exit = 1;
	j = k;
	while (line[j] != ' ' && line[j] != '\0')
	{
		i++;
		j++;
	}
	while (ft_strncmp(&line[k], l_env->key, i) != 0)
		l_env = l_env->next;
	return (l_env);
}

static char	*translate_ev(char *line, int k, t_env *l_env)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	l_env = get_ev(line, k, l_env);
	j = ft_strlen(line) - ft_strlen(l_env->key) + ft_strlen(l_env->value) + 1;
	newline = malloc(j * sizeof(char));
	if (newline == NULL)
		return (NULL);
	j = 0;
	while (line[i] != '\0')
	{
		if (i == k)
			newline = put_value(newline, &j, l_env->value);
		newline[j] = line[i];
		i++;
	}
	newline[j] = '\0';
	free(line);
	return (newline);
}

static int	check_ev(char *line, t_env *l_env)
{
	char	*key;
	int		i;
	int		result;

	i = 0;
	result = -1;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	while (l_env != NULL)
	{
		if (ft_strncmp(line, l_env->key, i) == 0)
			return (1);
		l_env = l_env->next;
	}
	return (0);
}

static char	*remove_backslash(char *line)
{
	char	*newline;
	int		i;
	int		j;

	newline = malloc(ft_strlen(line) * sizeof(char));
	if (newline == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] != 92)
		{
			newline[j] = line[i];
			j++;
		}
		i++;
	}
	newline[j] = '\0';
	free(line);
	return (newline);
}

void	expansor(char *line, t_env *l_env)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] != ' ' && i > 0 && line[i - 1] == 92)
			line = remove_backslash(line);
		else if (line[i] == '$' && line[i + 1] != ' ' && i > 0
			&& line[i - 1] != 92 && check_ev(&line[i], l_env) == 1)
			line = translate_ev(line, i, l_env);
		else if (line[i] == '$' && line[i + 1] != ' ' && i > 0
			&& line[i - 1] != 92 && check_ev(&line[i], l_env) == 0)
			line = remove_ev(line);
		i++;
	}
}
