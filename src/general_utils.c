/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpocater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:10:22 by rpocater          #+#    #+#             */
/*   Updated: 2024/07/27 14:19:26 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	*ft_token_and_parse(char *line, int *status)
{
	t_token	*list;
	t_com	*com;

	list = ft_tokenize(line);
	//if (list == NULL)
		//exit(EXIT_FAILURE);
	com = ft_lst_to_coms(list, status);
	ft_free_list(list);
	ft_countredir(com, status);
	//print_commands(com);
	free(line);
	return (com);
}
