/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:31:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/08/04 19:19:20 by rpocater         ###   ########.fr       */
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

void	unset(t_com *com, t_env *l_env, int *status)
{
	t_env	*aux;
	int		i;

	i = 1;
	*status = 0;
	if (com->command[i] == NULL)
		return ;
	while (l_env != NULL)
	{
		i = 1;
		while (com->command[i] != NULL)
		{
			if (ft_strcmp(l_env->key, com->command[i]) == 0)
			{
				aux = l_env;
				l_env = l_env->next;
				free (aux);
			}
			i++;
		}
		l_env = l_env->next;
	}
	*status = 0;
	return ;
}

void	del_env(t_env *l_env, t_env *del)
{
	while (l_env != NULL)
	{
		if (l_env == del)
		{
			l_env = l_env->next;
			free(del);
		}
		l_env = l_env->next;
	}
	return ;
}
