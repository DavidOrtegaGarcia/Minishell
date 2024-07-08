/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:20:49 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/08 17:33:59 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_coms(t_com *com)
{
        int     x;
        t_com   *elem;

        x = 0;
        while (com != NULL)
        {
		elem = com;
		com = com->next;
                while (elem->command[x] != NULL)
                {
			free(elem->command[x]);
                        x++;
                }
		free(elem->command);
		free(elem);
                x = 0;
        }
        return ;
}
