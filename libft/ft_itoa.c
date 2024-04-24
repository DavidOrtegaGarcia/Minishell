/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:01:50 by daortega          #+#    #+#             */
/*   Updated: 2024/02/12 17:11:02 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	static	get_num_digits(int n)
{
	int	n_digits;

	n_digits = 0;
	if (n < 0)
		n_digits++;
	if (n == 0)
		n_digits++;
	while (n != 0)
	{
		n /= 10;
		n_digits++;
	}
	return (n_digits);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		n_digits;
	long	num;

	n_digits = get_num_digits(n);
	num = (long)n;
	result = (char *) malloc((n_digits + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[n_digits--] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		num *= -1;
	}
	while (n_digits > 0)
	{
		result[n_digits--] = (num % 10) + 48;
		num /= 10;
	}
	if (n >= 0)
		result[0] = (num % 10) + 48;
	return (result);
}
