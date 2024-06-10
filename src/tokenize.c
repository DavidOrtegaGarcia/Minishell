/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:51:44 by rpocater          #+#    #+#             */
/*   Updated: 2024/06/10 15:21:34 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	ft_metachr(int c)
{
	int		i;
	char	*meta_char;

	i = 0;
	meta_char = " \t";
	while (meta_char[i] != '\0')
	{
		if (meta_char[i] == (char)c)
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
	len = (end - start);
	str = (char *) malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
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

	if(token_list == NULL)
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

t_token	*ft_tokenize(char *line)
{
	int		i;
	int		q_flag;
	int		start;
	int		word_flag;
	t_token		*token_list;

	i = 0;
	q_flag = 0;
	start = 0;
	word_flag = 0;
	token_list = NULL;	
	while (line[i] != '\0')
	{	
		if (ft_isprint(line[i]) == 1 && line[i] != ' ' && word_flag == 0 && q_flag == 0)
		{
			start = i;
			if (line[i] == '\"' || line[i] == '\'')
			{
				q_flag = 1;
				i++;
			}
			else
				word_flag = 1;
		}
		if ((ft_metachr(line[i]) == 1) && q_flag == 0 && word_flag == 1)
		{
			token_list = ft_addtoken(token_list, line, start, i);
			word_flag = 0;
		}
		if (q_flag == 1)
		{
			while (line[i] != line[start] && line[i] != '\0')
				i++;
			if (line[i + 1] == '\0' && line[i] != line[start])
			{
				printf("Finish quotes\n");
				return (NULL);
			}
			else
				token_list = ft_addtoken(token_list, line, start, i + 1);
			q_flag = 0;
		}
		i++;
	}
	if (word_flag == 1)
		token_list = ft_addtoken(token_list, line, start, i);
	print_list(token_list);
	return (token_list);
}
