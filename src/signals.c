/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:40:59 by daortega          #+#    #+#             */
/*   Updated: 2024/07/23 16:05:25 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_child(int sig)
{
	if (sig == CTRL_C)
		printf("\n");
}

static void	handler_default(int sig)
{
	if (sig == CTRL_C)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals(int process)
{
	if (process == DEFAULT)
		signal(CTRL_C, handler_default);
	else if (process == CHILD)
		signal(CTRL_C, handler_default);
	signal(CTRL_BS, handler_default);
}
