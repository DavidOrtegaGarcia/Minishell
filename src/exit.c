/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:28:31 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 14:33:10 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	is_digit(char *par)
{
	int	i;

	i = 0;
	if (par[0] == '-')
	{
		if (par[1] != '\0')
			i++;
		else
			return (0);
	}
	while (par[i] != '\0')
	{
		if (ft_isdigit(par[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_num(char *num, int neg)
{
	int		i;
	char	*number;

	if (!is_digit(num))
		return (1);
	number = ft_strdup(num);
	i = zerocase(number, neg);
	if ((neg == 0 && ft_strlen(&number[i]) > 19)
		|| (neg == 1 && ft_strlen(&number[i]) > 20))
		return (free(number), 1);
	if (neg == 0 && ft_strlen(&number[i]) == 19
		&& ft_strcmp(&number[i], "9223372036854775807") == 1)
		return (free(number), 1);
	if (neg == 1 && ft_strlen(&number[i]) == 20
		&& ft_strcmp(&number[i], "-9223372036854775808") == 1)
		return (free(number), 1);
	return (free(number), 0);
}

int	check_neg(char *num)
{
	if (num[0] == '-')
		return (1);
	return (0);
}

int	check_first_arg(char **com)
{
	int	num;
	int	neg;

	neg = check_neg(com[1]);
	ft_printf("exit\n");
	if (check_num(com[1], neg) == 1)
		return (ft_printf("exit: %s: numeric argument required\n", com[1]),
			exit(2), 2);
	else
	{
		if (com[2] != NULL)
		{
			ft_printf("exit: too many arguments\n");
			return (EXIT_FAILURE);
		}
		num = ft_atol(com[1]);
		exit(num % 256);
	}
}

int	ft_exit(char **com)
{
	if (com[1] == NULL)
		return (ft_printf("exit\n"), exit(EXIT_SUCCESS), EXIT_SUCCESS);
	return (check_first_arg(com));
}
