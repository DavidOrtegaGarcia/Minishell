/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:10:22 by rpocater          #+#    #+#             */
/*   Updated: 2024/08/26 16:31:37 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_x_env(t_env *l_env)
{
	while (l_env != NULL)
	{
		printf ("declare -x ");
		if (l_env->list == 1)
			printf("%s\n", l_env->key);
		if (l_env->list == 3)
			printf ("%s=\"%s\"\n", l_env->key, l_env->value);
		l_env = l_env->next;
	}
}

void	add_rep_node(t_env *aux, t_env *ret, int *tru)
{
	char	*del;

	del = aux->value;
	if (*tru == 2)
	{
		if (ret->value == NULL)
			return ;
		else if (aux->value == NULL)
			aux->value = ret->value;
		else
		{
			aux->value = ft_strjoin(aux->value, ret->value);
			free(ret->value);
		}
	}
	else
		aux->value = ret->value;
	free(del);
	if (aux->list == 1)
		aux->list = 3;
}

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
	if (ft_isalpha(key[0]) == 0)
		return (printf(MSG_NVF, key), *st = NVF, 0);
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
