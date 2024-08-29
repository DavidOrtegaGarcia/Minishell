/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:37:13 by rpocater          #+#    #+#             */
/*   Updated: 2024/08/29 15:34:16 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_protected_dup(char *elem)
{
	char	*ret;

	ret = ft_strdup(elem);
	if (ret == NULL)
	{
		return (perror(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
	}
	return (ret);
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
	t_token	*elem;
	int		i;

	elem = list;
	i = 0;
	while (elem != NULL)
	{
		ft_printf("Argument %d: %s\n", i, elem->content);
		elem = elem->next;
		i++;
	}
	return ;
}

int	ft_metachr(int c)
{
	char	*meta_char;
	char	*space;
	int		i;

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
