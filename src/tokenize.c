/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:51:44 by rpocater          #+#    #+#             */
/*   Updated: 2024/06/17 16:26:38 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	ft_metachr(int c)
{
	int		i;
	char	*meta_char;
	char	*space;

	i = 0;
	meta_char = "|<>";
	space = " \t";
	while (meta_char[i] != '\0')
	{
		if (space[i] == (char)c)
			return (1);
		if (meta_char[i] == (char)c)
			return (2);
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
	len = (end - start + 1);
	str = (char *) malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = line[start + i];
		i++;
	}
	str[i] = '\0';
	printf("Token: %s\n", str);
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

int	ft_addquote(char *line, int start, int x)
{
	int	i;

	i = x;
	while(line[i] != '\0')
	{
		if(line[i] == line[start])
			break ;
		i++;
	}
	if (line[i] != line[start] && line[i + 1] == '\0')
	{
		printf("Finish quotes \n");
		return (-1);
	}
	else
		i++;
	if (line[i] == '\'' || line[i] == '\"')
	{
		if (ft_addquote(line, i , i + 1) != -1)
			i = ft_addquote(line, i, i + 1);
	}
	return (i);
}

/*t_token	*ft_tokenize(char *line)
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
		if ((ft_metachr(line[i]) >= 1) && q_flag == 0 && word_flag == 1)
		{
			token_list = ft_addtoken(token_list, line, start, i - 1);
			word_flag = 0;
			if (ft_metachr(line[i]) == 2)
			{
				start = i;
				if (line[i] == '|')
				{
					token_list = ft_addtoken(token_list, line, start, i);
				}
				else
				{
					if(line[i + 1] == line[start])
						i++;
					token_list = ft_addtoken(token_list, line, start, i);
				}
			}
		}
		if (ft_metachr(line[i]) == 2)
		{
			start = i;
			if (line[i] == '|')
			{
				token_list = ft_addtoken(token_list, line, start, i);
			}
			else
			{
				if(line[i + 1] == line[start])
					i++;
				token_list = ft_addtoken(token_list, line, start, i);
			}
		}
		if (q_flag == 1)
		{
			i = ft_addquote(line, start, i);
			if (i != -1)
				token_list = ft_addtoken(token_list, line, start, i);
			q_flag = 0;
		}
		else
			i++;
	}
	if (word_flag == 1)
		token_list = ft_addtoken(token_list, line, start, i);
	//print_list(token_list);
	return (token_list);
}*/

t_token	*ft_tokenize(char *line)
{
	int		i;
	//int		q_flag;
	int		start;
	//int		word_flag;
	t_token		*token_list;

	i = 0;
	//q_flag = 0;
	start = 0;
	//word_flag = 0;
	token_list = NULL;
	while(line[i] != '\0')
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
		}
		else if(ft_metachr(line[i]) == 1)
		{
			i++;
		}
		else if(ft_metachr(line[i]) == 2)
		{
			start = i;
			if (line[i] == '|')
			{
				token_list = ft_addtoken(token_list, line, start, i);
			}
			else
			{
				if (line[i + 1] == line[start])
					i++;
				token_list = ft_addtoken(token_list, line, start, i);
			}
			i++;
		}
		else if((ft_isprint(line[i]) == 1) && (ft_metachr(line[i]) == 0))
		{
			start = i;
			while ((ft_metachr(line[i]) == 0) && (ft_isprint(line[i]) == 1))
				i++;
			token_list = ft_addtoken(token_list, line, start, i - 1);
		}
	}
	return (token_list);
}
