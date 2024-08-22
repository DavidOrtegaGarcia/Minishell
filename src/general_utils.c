/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:10:22 by rpocater          #+#    #+#             */
/*   Updated: 2024/08/22 15:06:38 by rpocater         ###   ########.fr       */
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

int	check_key(char *key, int *st)
{
	char	*metachar;
	int		i;
	int		j;

	metachar = "@#!$%^*-():;?/.,~+";
	i = 0;
	if (ft_strchr(key, '=') == 0)
		return (0);
	while (key[i] != '\0' && key[i] != '=')
	{
		if (key[i + 1] == '=' && key[i] == '+')
		{
			ft_memmove(key + i, key + i + 1, ft_strlen(key) - i);
			return (2);
		}
		j = 0;
		while (metachar[j] != '\0')
		{
			if (metachar[j] == key[i])
				return (printf(MSG_NVF, key), *st = NVF, -1);
			j++;
		}
		i++;
	}
	return (1);
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
