/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:10:22 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/31 16:25:04 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_content_com(t_com *elem, int i)
{
	t_redir	*red;
	int		x;

	x = 0;
	if (elem->command != NULL)
	{
		while (elem->command[x] != NULL)
		{
			printf("%s\n", elem->command[x++]);
		}
	}
	else
		printf("No contents in command %d\n", i);
	red = elem->redir;
	if (red != NULL)
	{
		printf("Command %d has redirections\n", i);
		while (red != NULL)
		{
			printf("Redirection type %d\n", red->type);
			printf("To file %s\n", red->file);
			red = red->next;
		}
	}
	return ;
}

t_com	*ft_token_and_parse(char *line, int *status)
{
	t_token	*list;
	t_com	*com;

	list = ft_tokenize(line);
	com = ft_lst_to_coms(list, status);
	ft_free_list(list);
	ft_countredir(com, status);
	free(line);
	return (com);
}
