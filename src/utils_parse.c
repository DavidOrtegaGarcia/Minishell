/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:20:49 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/29 15:28:39 by rpocater         ###   ########.fr       */
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

void	ft_free_redir(t_redir *original)
{
	t_redir	*red;

	while (original != NULL)
	{
		red = original;
		free(red->file);
		original = original->next;
		free(red);
	}
}

void	ft_free_coms(t_com *com)
{
	t_com	*elem;
	int		x;

	x = 0;
	while (com != NULL)
	{
		elem = com;
		com = com->next;
		if (elem->command != NULL)
		{
			while (elem->command[x] != NULL)
			{
				free(elem->command[x]);
				x++;
			}
		}
		free(elem->command);
		if (elem->redir != NULL)
		{
			ft_free_redir(elem->redir);
		}
		free(elem);
		x = 0;
	}
	return ;
}

t_redir	*ft_red_last(t_redir *elem)
{
	while (elem->next != NULL)
	{
		elem = elem->next;
	}
	return (elem);
}

void	free_dpchar(char **com)
{
	int	i;

	i = 0;
	if (com != NULL)
	{
		while (com[i] != NULL)
		{
			free(com[i]);
			i++;
		}
		free(com);
	}
	return ;
}
