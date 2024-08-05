/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:31:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/08/05 14:55:30 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

t_env	*ft_envlast(t_env *tkn)
{
	if (tkn != NULL)
	{
		while (tkn->next != NULL)
			tkn = tkn->next;
	}
	return (tkn);
}

void	single_export(t_com *com, t_env *l_env, int *tru, int i)
{
	t_env	*aux;
	t_env	*ret;
	char	*del;

	aux = l_env;
	ret = new_node(com->command[i]);
	while (aux != NULL)
	{
		if (ft_strcmp(aux->key, ret->key) == 0)
		{
			del = aux->value;
			aux->value = ft_strdup(ret->value);
			free(del);
			*tru = 1;
		}
		aux = aux->next;
	}
	if (*tru == 0)
		ft_envlast(l_env)->next = ret;
	else
	{
		free(ret->key);
		free(ret->value);
		free(ret);
	}
}

void	export(t_com *com, t_env *l_env, int *status)
{
	int	i;
	int	tru;

	i = 1;
	*status = 0;
	while (com->command[i] != NULL)
	{
		if (ft_strchr(com->command[i], '=') != 0)
		{
			tru = 0;
			single_export(com, l_env, &tru, i);
		}
		i++;
	}
	return ;
}

int	delete_one(t_env *l_env, char *one)
{
	t_env	*temp;
	t_env	*prev;

	temp = l_env;
	if (temp != NULL && ft_strcmp(temp->key, one) == 0)
	{
		prev = temp->next;
		free(temp->key);
		temp->key = prev->key;
		free(temp->value);
		temp->value = prev->value;
		temp->next = prev->next;
		return (free(prev), 0);
	}
	while (temp != NULL && ft_strcmp(temp->key, one) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	prev->next = temp->next;
	free(temp->key);
	free(temp->value);
	return (free(temp), 0);
}

void	unset(t_com *com, t_env *l_env, int *status)
{
	int	i;

	i = 1;
	*status = 0;
	while (com->command[i] != NULL)
	{
		*status = delete_one(l_env, com->command[i]);
		i++;
	}
	return ;
}
