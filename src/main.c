/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/07/24 17:45:31 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;
	t_com	*com;
	int	status;

	(void)argv;
	status = 0;
	if (argc != 1)
		return (perror(MSG_WNA), WNA);
	l_env = fill_l_env(env);
	if (l_env == NULL)
		return (perror(MSG_MLC_F), exit(MLC_F), MLC_F);
	//print_env(l_env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		if (line != NULL && line[0] != '\0')
			add_history(line);
		com = ft_token_and_parse(line, &status);
		print_commands(com);
		ft_free_coms(com);
		//line = expansor(line, l_env, status);
		line = readline("minishell$ ");
	}
	exit(EXIT_SUCCESS);
}
