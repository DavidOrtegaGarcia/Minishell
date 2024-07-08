/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <rpocater@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:52:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/08 15:36:05 by rpocater         ###   ########.fr       */
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
		return (NULL);
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

t_com	*ft_lst_to_coms(t_token *list)
{
	int	i;
	t_com	*ret;
	t_token	*elem;

	ret = NULL;
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
			return (NULL);
		ret->command = con_with_i(list, i);
		if (elem != NULL)
		{
			if (elem->content[0] == '|')
			{
				elem = elem->next;
				ret->next = ft_lst_to_coms(elem);
			}
		}
		else
			ret->next = NULL;
	}
	else
		printf("Syntax error at list to command conversion\n");
	return (ret);
}
