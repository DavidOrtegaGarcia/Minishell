/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:30:43 by daortega          #+#    #+#             */
/*   Updated: 2024/07/11 16:40:50 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*put_exstat(char *line, int pos_doll, int exstat, int j)
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

static char	*remove_ev(char *line, int i)
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

static int	check_ev(char *line, t_env *l_env)
{
	while (l_env != NULL)
	{
		if (compare_key(line, l_env->key) == 0)
			return (1);
		l_env = l_env->next;
	}
	return (0);
}

static char	*remove_char(char *line, int i)
{
	while (line[i] != '\0')
	{
		line[i] = line[i + 1];
		i++;
	}
	return (line);
}

static int	check_quotes(char *line, int *i, int *squotes, int *dquotes)
{
	int	remove;

	remove = 0;
	if (line[*i] == '"' && *dquotes == 1)
	{
		*dquotes = 0;
		remove = 1;
	}
	else if (line[*i] == '"' && *dquotes == 0 && *squotes == 0)
	{
		*dquotes = 1;
		remove = 1;
	}
	else if (line[*i] == '\'' && *squotes == 1)
	{
		*squotes = 0;
		remove = 1;
	}
	else if (line[*i] == '\'' && *squotes == 0 && *dquotes == 0)
	{
		*squotes = 1;
		remove = 1;
	}
	if (remove)
	{
		line = remove_char(line, *i);
		(*i)--;
		return (1);
	}
	return (0);
}

char	*expansor(char *line, t_env *l_env, int exstat)
{
	int	i;
	int	dquotes;
	int	squotes;

	dquotes = 0;
	squotes = 0;
	i = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		if (!check_quotes(line, &i, &squotes, &dquotes))
		{
			if (line[i] == '$' && squotes == 0 && line[i + 1] == '?')
				line = put_exstat(line, i, exstat, 0);
			else if (line[i] == '$' && squotes == 0
				&& ft_isalpha(line[i + 1]) == 1
				&& check_ev(&line[i + 1], l_env) == 1)
				line = translate_ev(line, i, l_env);
			else if (line[i] == '$' && squotes == 0
				&& ft_isalpha(line[i + 1]) == 1
				&& check_ev(&line[i + 1], l_env) == 0)
				line = remove_ev(line, i--);
			if (line == NULL)
				return (perror(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
		}
		i++;
	}
	/*if (dquotes == 1 || squotes == 1)
		return (printf("Sintaxis error\n"), free(line), NULL);*/
	return (line);
}
