/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:30:43 by daortega          #+#    #+#             */
/*   Updated: 2024/05/20 13:49:42 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void expansor(char *line, t_env *l_env)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && i > 0 && line[i - 1] == 92)
			line = remove_backslash();
		if (line[i] == '$' && i > 0 && line[i - 1] != 92 &&  
			check_ev(&line[i], l_env) == 1)
			line = translate_ev(line, l_env);
		if (line[i] == '$' && i > 0 && line[i - 1] != 92 &&  
			check_ev(&line[i], l_env) == 0)
			line = remove_ev(line);
		i++;
	}	
}
