/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:52:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/18 17:11:47 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	parse_input(int argc, char **argv, char **envp)
{
	if (argc <= 0)
	{
		printf("Running with no commands\n");
		return (-1);
	}
	if (envp[0] == NULL)
	{
		printf("running with no environment variables\n");
		return (-1);
	}
	if (argv[0][0] == '.' || argv[0][0] == '/' || argv[0][0] == '~')
		return (1);
	else
		return (2);
	return (0);
}

void	print_commands(t_com *com)
{
	int	i;
	int	x;
	t_com	*elem;

	elem = com;
	i = 0;
	x = 0;
	while (elem != NULL)
	{
		printf("Command %d: \n", i);
		while (elem->command[x] != NULL)
		{
			printf("%s\n", elem->command[x]);
			x++;
		}
		if (elem->redir != NULL)
		{
			printf("Command %d has redirections\n", i);
			while (elem->redir != NULL)
			{
				printf("Redirection type %d\n", elem->redir->type);
				printf("To file %s\n", elem->redir->file);
				elem->redir = elem->redir->next;
			}
		}
		elem = elem->next;
		i++;
		x = 0;
	}
	return ;
}

char	**con_with_i(t_token *list, int x)
{
	char	**ret;
	t_token	*elem;
	int	i;

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

t_redir	*ft_addredir(t_token **list, t_com *com, int *err)
{
	t_redir	*ret;

	ret = (t_redir *)malloc(sizeof(t_redir));
	if (ret == NULL)
		return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
	ret->type = ft_type_redir((*list)->content);
	*list = (*list)->next;
	if ((*list) == NULL)
		return (printf(MSG_AT_END), *err = AT_END, NULL);
	if (ft_metachr((*list)->content[0]) == 2)
	{
		*err = DBL_RE;
		return (printf(MSG_DBL_RE), NULL);
	}
	ret->file = ft_strdup((*list)->content);
	(*list) = (*list)->next;
	if (*list == NULL)
		return (ret);
	if ((*list)->content[0] == '|')
	{
		*list = (*list)->next;
		com->next = ft_lst_to_coms(*list, err);
	}
	else if (ft_metachr((*list)->content[0]) == 2)
	{
		ret->next = ft_addredir(list, com, err);
	}
	//else if (ft_isprint(list->content[0]) == 1)
		//return (printf(MSG_DBL_FILE), *err = DBL_FILE, NULL);
	return (ret);
}

t_com	*ft_lst_to_coms(t_token *list, int *err)
{
	int	i;
	t_com	*ret;
	t_token	*elem;
	t_redir *ered;

	ret = NULL;
	i = 0;
	elem = list;
	ret = (t_com *)malloc(sizeof(t_com));
	if (ret == NULL)
		return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
	ret->command = NULL;
	if (ft_metachr(elem->content[0]) == 2 && elem->content[0] != '|')
	{
		ret->redir = ft_addredir(&elem, ret, err);
	}
	list = elem;
	while (elem != NULL && ft_metachr(elem->content[0]) != 2)
	{
		elem = elem->next;
		i++;
	}
	if (i > 0)
	{
		//printf("I: %d\n", i);
		//ret = (t_com *)malloc(sizeof(t_com));
		//if (ret == NULL)
			//return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
		ret->command = con_with_i(list, i);
		//ret->redir = NULL;
	}
	if (elem != NULL)
	{
		if (elem->content[0] == '|')
		{
			elem = elem->next;
			ret->next = ft_lst_to_coms(elem, err);
		}
		else if (ft_metachr(elem->content[0]) == 2)
		{
			if (ret->redir != NULL)
			{
				ered = ft_red_last(ret->redir);
				ered->next = ft_addredir(&elem, ret, err);
			}
			else
				ret->redir = ft_addredir(&elem, ret, err);
		}
	}
	else
		ret->next = NULL;
	//}
	//else
	//{
	//	*err = SE_PIPE;
	//	return (printf(MSG_SE_PIPE), NULL);
	//}
	return (ret);
}
