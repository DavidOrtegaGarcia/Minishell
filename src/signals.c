/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:40:59 by daortega          #+#    #+#             */
/*   Updated: 2024/06/07 13:13:00 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
    if (sig == CTRL_C)
    {
        printf("\n");
        rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
    }
}
void    signals(void)
{
    signal(CTRL_C, handler);
	signal(CTRL_BS, handler);
}