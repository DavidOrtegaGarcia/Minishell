/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:51:44 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/29 16:20:42 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

char	*ft_strtoken(char *line, int start, int end)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = (end - start) + 1;
	str = (char *) malloc(len * sizeof(char) + 1);
	if (str == NULL)
		return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
	while (i < len)
	{
		str[i] = line[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_token	*ft_addtoken(t_token *token_list, char *line, int start, int end)
{
	t_token	*elem;
	t_token	*new;

	if (token_list == NULL)
	{
		token_list = (t_token *) malloc(sizeof(t_token));
		if (token_list == NULL)
			return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
		token_list->content = ft_strtoken(line, start, end);
		token_list->next = NULL;
	}
	else
	{
		new = (t_token *)malloc(sizeof(t_token));
		if (new == NULL)
			return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
		new->content = ft_strtoken(line, start, end);
		new->next = NULL;
		elem = ft_tokenlast(token_list);
		elem->next = new;
	}
	return (token_list);
}

int	ft_addquote(char *line, int start, int x)
{
	int	i;
	int	con;

	i = x;
	while (line[i] != '\0' && line[i] != line[start])
		i++;
	if ((line[i] != line[start]) && (line[i] == '\0'))
		return (ft_addend(line, i));
	else
		i++;
	con = ft_metachr(line[i]);
	if (con == 3)
	{
		i = ft_addquote(line, i, i + 1);
	}
	else if ((con == 3 || con == 0) && ft_isprint(line[i]) == 1)
	{
		while (line[i] != '\0' && ft_metachr(line[i]) == 0)
			i++;
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_addquote(line, i, i + 1);
	}
	return (i);
}

t_token	*ft_tokenize(char *line)
{
	t_token	*token_list;
	int		i;
	int		start;

	i = 0;
	start = 0;
	token_list = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			start = i++;
			i = ft_addquote(line, start, i);
			token_list = ft_addtoken(token_list, line, start, i - 1);
		}
		else if (ft_metachr(line[i]) == 1)
			i++;
		else if (ft_isprint(line[i]) == 1 && (ft_metachr(line[i]) == 0))
		{
			start = i;
			i = ft_addprint(line, i);
			token_list = ft_addtoken(token_list, line, start, i - 1);
		}
		else if (ft_metachr(line[i]) == 2)
		{
			start = i;
			i = ft_addmetachr(line, start, i);
			token_list = ft_addtoken(token_list, line, start, i);
			i++;
		}
		else
			i++;
	}
	return (token_list);
}
