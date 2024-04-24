/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:58:08 by daortega          #+#    #+#             */
/*   Updated: 2023/10/09 18:14:38 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*nodo;

	result = NULL;
	nodo = NULL;
	if (lst != NULL && f != NULL && del != NULL)
	{
		while (lst != NULL)
		{
			nodo = ft_lstnew(f(lst->content));
			if (nodo == NULL)
			{
				ft_lstclear(&result, del);
				return (NULL);
			}
			ft_lstadd_back(&result, nodo);
			lst = lst->next;
		}
	}
	return (result);
}
