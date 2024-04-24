/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:46:49 by daortega          #+#    #+#             */
/*   Updated: 2023/12/13 16:41:12 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnum(int num)
{
	char	*str;
	int		result;

	str = ft_itoa(num);
	if (str == NULL)
		return (-1);
	result = write(1, str, ft_strlen(str));
	free(str);
	return (result);
}

int	static	get_n_digits(unsigned int n)
{
	int	n_digits;

	n_digits = 0;
	if (n == 0)
		n_digits++;
	while (n != 0)
	{
		n /= 10;
		n_digits++;
	}
	return (n_digits);
}

char static	*unsitoa(unsigned int n)
{
	char			*result;
	int				n_digits;
	unsigned int	num;

	n_digits = get_n_digits(n);
	num = n;
	result = (char *) malloc((n_digits + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[n_digits--] = '\0';
	while (n_digits > 0)
	{
		result[n_digits--] = (num % 10) + 48;
		num /= 10;
	}
	result[0] = (num % 10) + 48;
	return (result);
}

int	ft_putunsnum(unsigned int num)
{
	char	*str;
	int		result;

	str = unsitoa(num);
	if (str == NULL)
		return (-1);
	result = write(1, str, ft_strlen(str));
	free(str);
	return (result);
}
