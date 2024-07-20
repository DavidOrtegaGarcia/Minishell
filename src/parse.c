/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:52:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/20 20:04:20 by rpocater         ###   ########.fr       */
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
		if (elem->command != NULL)
		{
			while (elem->command[x] != NULL)
			{
				printf("%s\n", elem->command[x]);
				x++;
			}
		}
		else
			printf("No contents in command %d\n", i);
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

void	ft_addredir(t_com *elem, int n_com, int n_red, int *err)
{
	int	i;
	char	**new_com;
	int 	tru;
	int	nci;
	t_redir	*red;

	i = 0;
	tru = 0;
	nci = 0;
	new_com = (char **)malloc(sizeof(char *) * (n_com + 1));
        if (new_com == NULL)
        {
                return (printf(MSG_MLC_F), exit(EXIT_FAILURE));
        }
	new_com[n_com + 1] = NULL;
	elem->redir = (t_redir *)malloc(sizeof(t_redir));
	if (elem->redir == NULL)
	{
		return (printf(MSG_MLC_F), exit(EXIT_FAILURE));
	}
	elem->redir->next = NULL;
	while (elem->command[i] != NULL)
	{
		if (ft_metachr(elem->command[i][0]) == 2 && tru == 0)
		{
			tru = 1;
			red = ft_red_last(elem->redir);
			red->type = ft_type_redir(elem->command[i]);
		}
		else if (ft_metachr(elem->command[i][0]) != 2 && tru == 1)
		{
			red->file = ft_strdup(elem->command[i]);
			red->next = NULL;
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
			new_com[nci] = ft_strdup(elem->command[i]);
			nci++;
		}
		i++;
	}
	printf("AFTER COMMAND CONVERSION\n");
	free_dpchar(elem->command);
	printf("xd\n");
	elem->command = new_com;
	return ;
}

void	ft_countredir(t_com *list, int *err)
{
	int	i;
	int	tru;
	int	n_com;
	int	n_red;
	t_com	*elem;

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
	printf("Command integrants : %i\nRedirection numbers : %i\n", n_com, n_red);
	//ft_addredir(elem, n_com, n_red, err);
	elem = elem->next;
	}
	return ;
}

t_com	*ft_lst_to_coms(t_token *list, int *err)
{
	int	i;
	t_com	*ret;
	t_token	*elem;

	i = 0;
	elem = list;
	while (elem != NULL && elem->content[0] != '|')
	{
		elem = elem->next;
		i++;
	}
	if (i > 0)
	{
		printf("I: %d\n", i);
		ret = (t_com *)malloc(sizeof(t_com));
		if (ret == NULL)
			return (printf(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
		ret->command = con_with_i(list, i);
		ret->redir = NULL;
		if (elem != NULL)
		{
			if (elem->content[0] == '|')
			{
				elem = elem->next;
				ret->next = ft_lst_to_coms(elem, err);
			}
			else
				ret->next = NULL;
		}
		else
			ret->next = NULL;
	}
	else
	{
		*err = SE_PIPE;
		return (printf(MSG_SE_PIPE), NULL);
	}
	return (ret);
}
