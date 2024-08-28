/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/08/20 16:03:29 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	int		status;
	char	*line;
	t_env	*l_env;
	t_com	*com;

	(void)argv;
	status = 0;
	if (argc != 1)
		return (perror(MSG_WNA), WNA);
	signals(DEFAULT);
	l_env = fill_l_env(env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		if (line[0] != '\0')
			add_history(line);
		com = ft_token_and_parse(line, &status);
		expansor(com, l_env, status);
		heredoc(com);
		execute(com, &l_env, &status);
		signals(DEFAULT);
		//clean_heredoc(com);
		ft_free_coms(com);
		line = readline("minishell$ ");
	}
	return (exit(EXIT_SUCCESS), 0);
}
