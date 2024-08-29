/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:37:24 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 14:44:01 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static char	*insert_exstat(char *newline, int *i, char *cexstat)
{
	int	j;

	j = 0;
	while (cexstat[j] != '\0')
	{
		newline[*i] = cexstat[j];
		(*i)++;
		j++;
	}
	(*i)--;
	return (newline);
}

char	*put_exstat(char *line, int pos_doll, int exstat, int j)
{
	char	*cexstat;
	char	*newline;
	int		i;

	cexstat = ft_itoa(exstat);
	if (cexstat == NULL)
		return (free(line), NULL);
	newline = malloc((ft_strlen(line) + ft_strlen(cexstat) - 1) * sizeof(char));
	if (newline == NULL)
		return (free(cexstat), free(line), NULL);
	i = 0;
	while (line[j] != '\0')
	{
		if (i == pos_doll)
		{
			newline = insert_exstat(newline, &i, cexstat);
			j++;
		}
		else
			newline[i] = line[j];
		i++;
		j++;
	}
	newline[i] = '\0';
	return (free(cexstat), free(line), newline);
}

char	*remove_ev(char *line, int i)
{
	int	j;

	j = i + 1;
	while (ft_isalpha(line[j]) == 1)
		j++;
	while (line[j] != '\0')
	{
		line[i] = line[j];
		i++;
		j++;
	}
	line[i] = line[j];
	return (line);
}

static char	*put_value(char *newline, int *j, char *value)
{
	int	i;

	i = 0;
	while (value[i] != '\0')
	{
		newline[*j] = value[i];
		(*j)++;
		i++;
	}
	return (newline);
}

char	*translate_ev(char *line, int k, t_env *l_env)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	l_env = get_ev(line, k + 1, l_env);
	j = ft_strlen(line) - ft_strlen(l_env->key) + ft_strlen(l_env->value);
	newline = malloc(j * sizeof(char));
	if (newline == NULL)
		return (free(line), NULL);
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
