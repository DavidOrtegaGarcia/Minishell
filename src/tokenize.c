/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:51:44 by rpocater          #+#    #+#             */
/*   Updated: 2024/05/23 13:23:34 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	quote_len(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != c)
		i++;
	return (i);
}

int	word_len(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0' && line[i] != '"' && line[i] != '\'' && line[i] != ' ' && ft_isprint(line[i]) == 1)
	{
		i++;
	}
	return (i);
}
char	**ft_tokenize(char *line)
{
	int		i;
	int		quote_pair;
	int		d_quote_pair;
	//int		meta_characters;
	int		num_quote;
	int 	num_d_quote;
	int		token_count;
	int 	word_flag;
	int		token_len;
	int		token_start;
	char	**ret;

	i = 0;
	num_quote = 0;
	num_d_quote = 0;
	quote_pair = 0;
	d_quote_pair = 0;
	//meta_characters = 0;
	token_count = 0;
	word_flag = 0;
	token_len = 0;
	token_start = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && quote_pair == 0 && d_quote_pair == 0)
		{
			if (word_flag == 1)
			{
				word_flag = 0;
				token_count++;
			}
			quote_pair = 1;
		}
		if (line[i] == '"' && quote_pair == 0 && d_quote_pair == 0)
		{
			if (word_flag == 1)
			{
				word_flag = 0;
				token_count++;
			}
			d_quote_pair = 1;
		}
		if (line[i] == '\'' && quote_pair == 1)
		{
			num_quote++;
			quote_pair = 0;
			token_count++;
		}
		if (line[i] == '"' && d_quote_pair == 1)
		{
			num_d_quote++;
			d_quote_pair = 0;
			token_count++;
		}
		if ((line[i] == ' ' || line[i + 1] == '\0' || (line[i] >= 9 && line[i] <= 13)) && word_flag == 1)
		{
			word_flag = 0;
			token_count++;
		}
		if (ft_isprint(line[i]) == 1 && line[i] != ' ' && word_flag == 0 && quote_pair == 0 && d_quote_pair == 0)
		{
			word_flag = 1;
		}
		i++;
	}
	if (quote_pair == 1)
	{
		//in this place you need to ask for quote to finish the quoting
		printf("Ask for quote\n");
		return (NULL);
	}
	if (d_quote_pair == 1)
	{
		//same as before but with double quotes
		printf("Ask for double quotes\n");
		return (NULL);
	}
	if (token_count <= 0)
		return (printf("No tokens counted\n"), NULL);
	ret = (char **) malloc((token_count + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		//count the amount of arguments this haves taking into account the quoting rules
		//in order to reserve memory later on
		if (line[i] == '\'' && num_quote > 0 && token_start < token_count)
		{
			i++;
			token_len = quote_len(line + i, '\'');
			ret[token_start] = malloc((token_len + 3) * sizeof(char));
			if (ret[token_start] == NULL)
				return (NULL);
			ret[token_start][0] = '\'';
			ft_memcpy(ret[token_start] + 1, line + i, token_len);
			ret[token_start][token_len + 1] = '\'';
			ret[token_start][token_len + 2] = '\0';
			token_start++;
			num_quote--;
			i = i + token_len + 1;
		}
		if (line[i] == '"' && num_d_quote > 0 && token_start < token_count)
		{
			i++;
			token_len = quote_len(line + i, '"');
			ret[token_start] = malloc((token_len + 3) * sizeof(char));
			if (ret[token_start] == NULL)
				return (NULL);
			ret[token_start][0] = '"';
			ft_memcpy(ret[token_start] + 1, line + i, token_len);
			ret[token_start][token_len + 1] = '"';
			ret[token_start][token_len + 2] = '\0';
			token_start++;
			num_d_quote--;
			i = i + token_len + 1;
		}
		if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		{
			i++;
		}
		if (ft_isprint(line[i]) == 1 && line[i] != ' ' && token_start < token_count)
		{
			token_len = word_len(line + i);
			ret[token_start] = malloc((token_len + 1) * sizeof(char));
			ft_memcpy(ret[token_start], line + i, token_len);
			ret[token_start][token_len + 1] = '\0';
			token_start++;
			i = i + token_len + 1;
		}
	}
	ret[token_start] = NULL;
	return	(ret);
}
