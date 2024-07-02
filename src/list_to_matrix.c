/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:20:33 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/02 12:49:17 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

char	**ft_lst_to_matrix(t_token *list)
{
	int	i;
	char	**ret;
	t_token	*elem;

	ret = NULL;
	i = 0;
	if(list != NULL)
	{
		elem = list;
		while (elem != NULL)
		{
			elem = elem->next;
			i++;
		}
	}
	if (i > 0)
	{
		ret = (char **)malloc(sizeof(char *) * (i + 1));
		if (ret == NULL)
			return (NULL);
		elem = list;
		i = 0;
		while (elem != NULL)//possible problem
		{
			*(ret + i) = ft_strdup(elem->content);	
			elem = elem->next;
			i++;
		}
	}
	*(ret + i) = NULL;
	ft_free_list(list);
	return (ret);
}
