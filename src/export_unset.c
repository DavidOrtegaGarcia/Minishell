/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:31:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/08/26 15:17:34 by rpocater         ###   ########.fr       */
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

void	single_export(char *com, t_env *l_env, int *tru)
{
	t_env	*aux;
	t_env	*ret;
	char	*del;

	aux = l_env;
	ret = new_node(com);
	while (aux != NULL)
	{
		if (ft_strcmp(aux->key, ret->key) == 0)
		{
			del = aux->value;
			if (*tru == 2)
			{
				aux->value = ft_strjoin(aux->value, ret->value);
				free(ret->value);
			}
			else
				aux->value = ret->value;
			free(del);
			if (aux->list == 1)
				aux->list = 3;
			*tru = 0;
		}
		aux = aux->next;
	}
	if (*tru != 0)
		ft_envlast(l_env)->next = ret;
	else
	{
		free(ret->key);
		free(ret);
	}
}

void	export(t_com *com, t_env **l_env, int *status)
{
	int	i;
	int	tru;

	i = 1;
	*status = 0;
	if (com->command[i] == NULL)
		print_x_env(*l_env);
	while (com->command[i] != NULL)
	{
		tru = check_key(com->command[i], status);
		if (tru > 0)
		{
			if (*l_env == NULL)
				*l_env = new_node(com->command[i]);
			else
				single_export(com->command[i], *l_env, &tru);
		}
		i++;
	}
	return ;
}

int	delete_one(t_env **l_env, char *one)
{
	t_env	*temp;
	t_env	*prev;

	temp = *l_env;
	if (temp != NULL && ft_strcmp(temp->key, one) == 0)
	{
		*l_env = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return (0);
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

void	unset(t_com *com, t_env **l_env, int *status)
{
	int	i;

	i = 1;
	while (com->command[i] != NULL)
	{
		*status = delete_one(l_env, com->command[i]);
		i++;
	}
	return ;
}
