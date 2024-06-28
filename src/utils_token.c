/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:37:13 by rpocater          #+#    #+#             */
/*   Updated: 2024/06/27 15:08:20 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_lines(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	ft_free_list(t_token *list)
{
	t_token	*elem;

	while (list != NULL)
	{
		elem = list;
		list = list->next;
		free(elem->content);
		free(elem);
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
	if ((char)c == '\'' || (char)c == '\"')
		return (3);
	return (0);
}
