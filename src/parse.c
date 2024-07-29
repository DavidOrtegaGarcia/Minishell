/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:52:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/29 16:10:46 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	print_commands(t_com *com)
{
	t_com	*elem;
	int		i;

	elem = com;
	i = 0;
	while (elem != NULL)
	{
		printf("Command %d: \n", i);
		print_content_com(elem, i);
		elem = elem->next;
		i++;
	}
	return ;
}

char	**con_with_i(t_token *list, int x)
{
	char	**ret;
	t_token	*elem;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (x + 1));
	if (ret == NULL)
	{
		return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
	}
	elem = list;
	i = 0;
	while (elem != NULL && i < x)
	{
		*(ret + i) = ft_strdup(elem->content);
		elem = elem->next;
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}

void	ft_addredir(t_com *elem, int n_com, int *err)
{
	char	**new_com;
	t_redir	*red;
	int		i;
	int		tru;
	int		nci;

	i = 0;
	tru = 0;
	nci = 0;
	red = NULL;
	if (n_com != 0)
	{
		new_com = (char **)malloc(sizeof(char *) * (n_com + 1));
		if (new_com == NULL)
			return (printf(MSG_MLC_F), exit(EXIT_FAILURE));
	}
	else
		new_com = NULL;
	while (elem->command[i] != NULL)
	{
		if (ft_metachr(elem->command[i][0]) == 2 && tru == 0)
		{
			tru = 1;
			red = (t_redir *)malloc(sizeof(t_redir));
			if (red == NULL)
			{
				*err = MLC_F;
				return (printf(MSG_MLC_F), exit(EXIT_FAILURE));
			}
			red->type = ft_type_redir(elem->command[i]);
		}
		else if (ft_metachr(elem->command[i][0]) != 2 && tru == 1)
		{
			red->file = ft_strdup(elem->command[i]);
			red->next = NULL;
			if (elem->redir == NULL)
				elem->redir = red;
			else
				(ft_red_last(elem->redir))->next = red;
			tru = 0;
		}
		else if (ft_metachr(elem->command[i][0]) != 2 && tru == 0)
		{
			new_com[nci] = ft_strdup(elem->command[i]);
			nci++;
		}
		i++;
	}
	free_dpchar(elem->command);
	if (new_com != NULL)
		new_com[nci] = NULL;
	elem->command = new_com;
}

void	ft_countredir(t_com *list, int *err)
{
	t_com	*elem;
	int		i;
	int		tru;
	int		n_com;
	int		n_red;

	elem = list;
	while (elem != NULL)
	{
		i = 0;
		n_com = 0;
		n_red = 0;
		tru = 0;
		while (elem->command[i] != NULL)
		{
			if (ft_metachr(elem->command[i][0]) == 2 && tru == 0)
			{
				tru = 1;
			}
			else if (ft_metachr(elem->command[i][0]) != 2 && tru == 1)
			{
				n_red++;
				tru = 0;
			}
			else if (ft_metachr(elem->command[i][0]) == 2 && tru == 1)
			{
				*err = DBL_RE;
				printf(MSG_DBL_RE);
				return ;
			}
			else if (ft_metachr(elem->command[i][0]) != 2 && tru == 0)
			{
				n_com++;
			}
			i++;
		}
		if (tru == 1)
		{
			*err = AT_END;
			printf(MSG_AT_END);
			return ;
		}
		ft_addredir(elem, n_com, err);
		elem = elem->next;
	}
	return ;
}

t_com	*ft_lst_to_coms(t_token *list, int *err)
{
	t_com	*ret;
	t_token	*elem;
	int		i;

	i = 0;
	elem = list;
	ret = NULL;
	while (elem != NULL && elem->content[0] != '|')
	{
		elem = elem->next;
		i++;
	}
	if (i > 0)
	{
		ret = (t_com *)malloc(sizeof(t_com));
		if (ret == NULL)
			return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
		ret->command = con_with_i(list, i);
		ret->redir = NULL;
		ret->next = NULL;
		if (elem != NULL)
		{
			if (elem->content[0] == '|')
			{
				elem = elem->next;
				if (elem == NULL)
					return (*err = SE_PIPE, printf(MSG_SE_PIPE), ret);
				ret->next = ft_lst_to_coms(elem, err);
			}
		}
	}
	else if (elem != NULL && elem->content[0] == '|')
		return (*err = SE_PIPE, printf(MSG_SE_PIPE), NULL);
	return (ret);
}
