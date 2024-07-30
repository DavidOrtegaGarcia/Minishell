/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/30 16:58:35 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

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

int	count_subcom(t_com *elem, int i, int n_com, int *err)
{
	int	tru;

	tru = 0;
	while (elem->command[i] != NULL)
	{
		if (ft_metachr(elem->command[i][0]) == 2 && tru == 0)
			tru = 1;
		else if (ft_metachr(elem->command[i][0]) != 2 && tru == 1)
			tru = 0;
		else if (ft_metachr(elem->command[i][0]) == 2 && tru == 1)
			return (*err = DBL_RE, printf(MSG_DBL_RE), -1);
		else if (ft_metachr(elem->command[i][0]) != 2 && tru == 0)
			n_com++;
		i++;
	}
	if (tru == 1)
		return (*err = AT_END, printf(MSG_AT_END), -1);
	return (n_com);
}
