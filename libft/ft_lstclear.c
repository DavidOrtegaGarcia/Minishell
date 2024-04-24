/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:16:34 by daortega          #+#    #+#             */
/*   Updated: 2023/10/09 15:52:14 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	if (*lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			aux = *lst;
			del((*lst)->content);
			*lst = (*lst)->next;
			free(aux);
		}
	}
}
