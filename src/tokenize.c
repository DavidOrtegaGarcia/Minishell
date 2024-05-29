/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:51:44 by rpocater          #+#    #+#             */
/*   Updated: 2024/05/29 14:02:40 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	ft_metachr(int c)
{
	int		i;
	char	*meta_char;

	i = 0;
	meta_char = " \t|<>";
	while (meta_char[i] != '\0')
	{
		if (meta_char[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

t_token	*ft_lstnew(char *content)
{
	t_list	*newlist;

	newlist = (t_list *) malloc(sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}

void	ft_addtoken(t_token *token_list, char *line, int start, int end)
{
	if (token_list == NULL)
	{
		token_list = (t_token *) malloc(sizeof(t_list));
		if (token_list == NULL)
			return (printf("Malloc fail at creating first token\n"));
		token_list->content = line[end - start];// make the char dup
		token_list->next = NULL;
		return ;
	}
	else
	{
		//make lst addback
	if (lst != NULL && *lst != NULL)
	{
		elem = *lst;
		elem = ft_lstlast(*lst);
		elem->next = new;
		return ;
	}
	*lst = new;
	}
}

char	**ft_tokenize(char *line)
{
	int		i;
	int		q_flag;
	int		start;
	int		word_flag;
	t_token	*token_list;

	i = 0;
	q_flag = 0;
	start = 0;
	word_flag = 0;
	token_list = NULL;	
	while (line[i] != '\0')
	{	
		if (ft_isprint(line[i]) == 1 && line[i] != ' ' && word_flag == 0 && q_flag = 0)
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
		if (ft_metachr(line[i]) == 1 && q_flag == 0 && word_flag == 1)
		{
			if (token_list == NULL)
				ft_lstnew(line[i - start]);
			else
				ft_lstaddback(line[i - start]);
			word_flag == 0;
		}
		if (q_flag == 1)
		{
			while (line[i] != line[start] && line[i] != '\0')
				i++;
			if (line[i + 1] == '\0')
			{
				printf("Finish quotes\n");
				return ;
			}
			else
				ft_addtoken(token_list, line, start, i);
			q_flag == 0;
		}
		i++;
	}
}
