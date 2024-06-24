/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:51:44 by rpocater          #+#    #+#             */
/*   Updated: 2024/06/24 16:57:11 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	ft_metachr(int c)
{
	int	i;
	char	*meta_char;
	char	*space;

	i = 0;
	meta_char = "|<>";
	space = " \t";
	while (meta_char[i] != '\0')
	{
		if (meta_char[i] == (char)c)
			return (2);
		i++;
	}
	i = 0;
	while (space[i] != '\0')
	{
		if (space[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

t_token	*ft_tokenlast(t_token *tkn)
{
	if (tkn != NULL)
	{
		while (tkn->next != NULL)
			tkn = tkn->next;
	}
	return (tkn);
}

char	*ft_strtoken(char *line, int start, int end)
{
	char	*str;
	int	len;
	int	i;

	i = 0;
	len = (end - start) + 1;
	str = (char *) malloc(len * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = line[start + i];
		i++;
	}
	str[i] = '\0';
	printf("Final Token: %s\n", str);
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
		{
			printf("Malloc fail at creating token\n");
			return (NULL);
		}
		token_list->content = ft_strtoken(line, start, end);
		token_list->next = NULL;
	}
	else
	{
		new = (t_token *)malloc(sizeof(t_token));
		if (new == NULL)
			return (NULL);
		new->content = ft_strtoken(line, start, end);
		new->next = NULL;
		elem = ft_tokenlast(token_list);
		elem->next = new;
	}
	return (token_list);
}

void	print_list(t_token *list)
{
	int	i;
	t_token	*elem;

	elem = list;
	i = 0;
	while (elem != NULL)
	{
		printf("Argument %d: %s\n", i, elem->content);
		elem = elem->next;
		i++;
	}
	return ;
}

int	ft_addquote(char *line, int start, int x)
{
	int	i;

	i = x;
	while (line[i] != '\0')
	{
		if (line[i] == line[start])
			break ;
		i++;
	}
	if ((line[i] != line[start]) && (line[i] == '\0'))
	{
		return (-1);
	}
	else
		i++;
	if (line[i] == '\'' || line[i] == '\"')
	{
		if (ft_addquote(line, i, i + 1) != -1)
			i = ft_addquote(line, i, i + 1);
	}
	else if (ft_metachr(line[i]) == 0 && ft_isprint(line[i]) == 1)
	{
		while (line[i] != '\0' && ft_metachr(line[i]) == 0 && line[i] != '\'' && line[i] != '\"')
		{
			i++;
		}
		if (line[i] == '\'' || line[i] == '\"')
			if (ft_addquote(line, i, i + 1) != -1)
				i = ft_addquote(line, i, i + 1);
	}
	return (i);
}

t_token	*ft_tokenize(char *line)
{
	int		i;
	int		start;
	t_token		*token_list;

	i = 0;
	start = 0;
	token_list = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			start = i;	
			i++;
			i = ft_addquote(line, start, i);
			if (i != -1)
			{
				token_list = ft_addtoken(token_list, line, start, i - 1);
			}
			else
			{
				printf("Finish quotes\n");
				//token_list = ft_addtoken(token_list, line, start, i - 1);
				return (token_list);
			}
		}
		else if (ft_metachr(line[i]) == 1)
			i++;
		else if (ft_metachr(line[i]) == 2)
		{
			start = i;
			if (line[i] == '|')
				token_list = ft_addtoken(token_list, line, start, i);
			else
			{
				if (line[i + 1] == line[start])
					i++;
				token_list = ft_addtoken(token_list, line, start, i);
			}
			i++;
		}
		else if ((ft_isprint(line[i]) == 1) && (ft_metachr(line[i]) == 0))
		{
			start = i;
			while ((ft_metachr(line[i]) == 0) && (ft_isprint(line[i]) == 1))
				i++;
			token_list = ft_addtoken(token_list, line, start, i - 1);
		}
	}
	return (token_list);
}
