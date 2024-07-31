/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/31 17:06:54 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

t_com	*prepare_com(t_token *list, t_token *elem, int i, int *err)
{
	t_com	*ret;

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
				return (*err = SE_PIPE * -1, printf(MSG_SE_PIPE), ret);
			ret->next = ft_lst_to_coms(elem, err);
		}
	}
	return (ret);
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
			return (*err = DBL_RE * -1, printf(MSG_DBL_RE), -1);
		else if (ft_metachr(elem->command[i][0]) != 2 && tru == 0)
			n_com++;
		i++;
	}
	if (tru == 1)
		return (*err = AT_END * -1, printf(MSG_AT_END), -1);
	return (n_com);
}

t_redir	*first_redir(t_com *elem, int *err, int *tru, int i)
{
	t_redir	*red;

	red = NULL;
	*tru = 1;
	red = (t_redir *)malloc(sizeof(t_redir));
	if (red == NULL)
	{
		*err = MLC_F * -1;
		printf(MSG_MLC_F);
		return (exit(EXIT_FAILURE), NULL);
	}
	red->type = ft_type_redir(elem->command[i]);
	return (red);
}

void	second_redir(t_com *elem, t_redir *red, int i, int *tru)
{
	red->file = ft_strdup(elem->command[i]);
	red->next = NULL;
	if (elem->redir == NULL)
		elem->redir = red;
	else
		(ft_red_last(elem->redir))->next = red;
	*tru = 0;
}

char	**generate_new_com(int *n_com)
{
	char	**new_com;

	if (*n_com != 0)
	{
		new_com = (char **)malloc(sizeof(char *) * (*(n_com) + 1));
		if (new_com == NULL)
			return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
	}
	else
		new_com = NULL;
	*n_com = 0;
	return (new_com);
}
