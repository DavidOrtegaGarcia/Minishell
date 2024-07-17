/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:20:49 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/16 14:12:36 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	ft_type_redir(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
                return (HERE_DOC);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (OUT_APPEND);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (IN);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (OUT_TRUNC);
	else
		return (REDIRECT_NONE);

}
void	ft_free_coms(t_com *com)
{
        int     x;
        t_com   *elem;
	t_redir *red;

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
		while (elem->redir != NULL)
		{
			red = elem->redir;
			elem->redir = elem->redir->next;
			//free(red->type);
			free(red->file);
			free(red);	
		}
		free(elem);
                x = 0;
        }
        return ;
}
