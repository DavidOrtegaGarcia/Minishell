/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:10:22 by rpocater          #+#    #+#             */
/*   Updated: 2024/08/01 15:11:53 by daortega         ###   ########.fr       */
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

	if (line == NULL || line[0] == '\0')
		return (free(line), NULL);
	list = ft_tokenize(line);
	com = ft_lst_to_coms(list, status);
	ft_free_list(list);
	free(line);
	if (*status < 0)
	{
		*status *= -1;
		ft_free_coms(com);
		return (NULL);
	}
	ft_countredir(com, status);
	if (*status < 0)
	{
		*status *= -1;
		ft_free_coms(com);
		return (NULL);
	}
	return (com);
}
