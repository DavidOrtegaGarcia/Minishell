/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:30:43 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 14:40:17 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_char(char *line, int i)
{
	while (line[i] != '\0')
	{
		line[i] = line[i + 1];
		i++;
	}
	return (line);
}

static char	*expan(char *line, int *i, t_env *l_env, t_utils_exp utils)
{
	if (line[*i] == '$' && utils.squotes == 0 && line[*i + 1] == '?')
		line = put_exstat(line, *i, utils.exstat, 0);
	else if (line[*i] == '$' && utils.squotes == 0
		&& ft_isalpha(line[*i + 1]) == 1
		&& check_ev(&line[*i + 1], l_env) == 1)
		line = translate_ev(line, *i, l_env);
	else if (line[*i] == '$' && utils.squotes == 0
		&& ft_isalpha(line[*i + 1]) == 1
		&& check_ev(&line[*i + 1], l_env) == 0)
		line = remove_ev(line, (*i)--);
	return (line);
}

static int	check_quotes(char *line, int *i, int *squotes, int *dquotes)
{
	int	remove;

	remove = *dquotes + *squotes;
	if (line[*i] == '"' && *dquotes == 1)
		*dquotes = 0;
	else if (line[*i] == '"' && *dquotes == 0 && *squotes == 0)
		*dquotes = 1;
	else if (line[*i] == '\'' && *squotes == 1)
		*squotes = 0;
	else if (line[*i] == '\'' && *squotes == 0 && *dquotes == 0)
		*squotes = 1;
	if (remove != *dquotes + *squotes)
	{
		line = remove_char(line, *i);
		(*i)--;
		return (1);
	}
	return (0);
}

static char	*make_expansor(char *line, t_env *l_env, int exstat)
{
	int			i;
	int			dquotes;
	int			squotes;
	t_utils_exp	utils;

	utils.exstat = exstat;
	dquotes = 0;
	squotes = 0;
	i = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		if (!check_quotes(line, &i, &squotes, &dquotes))
		{
			utils.squotes = squotes;
			line = expan(line, &i, l_env, utils);
			if (line == NULL)
				return (perror(MSG_MLC_F), exit(MLC_F), NULL);
		}
		i++;
	}
	return (line);
}

void	expansor(t_com *com, t_env *l_env, int exstat)
{
	int	i;

	i = 0;
	while (com != NULL)
	{
		i = 0;
		while (com->command != NULL && com->command[i] != NULL)
		{
			com->command[i] = make_expansor(com->command[i], l_env, exstat);
			i++;
		}
		com = com->next;
	}
}
