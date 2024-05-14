/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:51:44 by rpocater          #+#    #+#             */
/*   Updated: 2024/05/14 14:56:40 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

char	**ft_tokenize(char *line)
{
	int	i;
	int	num_quotes;
	int	num_double_quotes;
	int	meta_characters;

	i = 0;
	num_quotes = 0;
	num_double_quotes = 0;
	meta_characters = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ''')
			num_quotes++;
		else if(line[i] == '"')
			num_double_quotes++;
		i++;
	}
	if (num_quotes % 2 != 0)
	{
		//in this place you need to ask for quote to finish the quoting
		printf("Ask for quote\n");
	}
	if (num_double_quotes % 2 != 0)
	{
		//same as before but with double quotes
		printf("Ask for double quotes\n");
	}
	i = 0;
	while (line[i] != '\0')
	{
		//count the amount of arguments this haves taking into account the quoting rules
		//in order to reserrve memory later on
	}	
}
